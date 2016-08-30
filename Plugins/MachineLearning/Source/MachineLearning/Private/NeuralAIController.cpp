// Robert Chubb - Saxon Rah - Parabolic Labs
// Neural AIController
#include "MachineLearningPrivatePCH.h"
#include "DrawDebugHelpers.h"
#include "NeuralAIController.h"


static FORCEINLINE bool Trace(
	UWorld* World,
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Pawn,
	bool ReturnPhysMat = false
) {
	if (!World) { return false; }

	FCollisionQueryParams TraceParams(FName(TEXT("NeuralNet Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingleByChannel(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
	);

	//HitOut.GetFirstBlockingHit().IsValidBlockingHit();
	//Hit any Actor?
	return HitOut.IsValidBlockingHit();
}

void ANeuralAIController::BeginPlay()
{
	Super::BeginPlay();

	// Setup Neurological Mappings
	TArray<int32> NeurologicalMap;
	NeurologicalMap.Add(3); //Inputs
	NeurologicalMap.Add(6); //Hidden
	NeurologicalMap.Add(2); //Outputs

	Network = SpawnBP<ANeuralNet>(GetWorld(), NetToSpawn, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	
	Network->TransferType = ETransferType::TT_Tanh;
	Network->NetTrainingRate = 0.15f;
	Network->NetMomentum = 0.5f;

	Network->Setup(NeurologicalMap, Network->TransferType, Network->NetTrainingRate, Network->NetMomentum);
}


void ANeuralAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Simulate(true);
}

float ANeuralAIController::LineTrace(float IncomingSightDistance, float IncomingAngle)
{
	//In player controller class

	//location the PC is focused on
	//const FVector Start = GetFocalPoint();
	const FVector Start = GetPawn()->GetActorLocation();
	const FVector PawnFWDVec = GetPawn()->GetActorForwardVector();

	//256 units in facing direction of PC (256 units in front of the camera)
	//const FVector End = Start + GetControlRotation().Vector() * IncomingSightDistance;
	const FVector End = Start + FVector(PawnFWDVec * IncomingSightDistance).RotateAngleAxis(IncomingAngle, FVector(0.0f, 0.0f, 1.0f));

	//The trace data is stored here
	FHitResult HitData(ForceInit);

	//If Trace Hits anything	
	bool bTraceState = Trace(GetWorld(), GetPawn(), Start, End, HitData);

	//DrawDebugLine(GetWorld(), Start, End, FColor(255, 0, 0), false, 0.1f, 0, 0.1f);
	//DrawDebugPoint(GetWorld(), HitData.ImpactPoint, 5.0f, FColor(0, 0, 255), false, 0.1f, 0);

	return bTraceState == true ? (HitData.ImpactPoint - Start).Size() : -1.0f;
	//return (HitData.ImpactPoint - Start).Size();
}

void ANeuralAIController::Simulate(bool IncomingIsLearning)
{
	ImpactLeft = LineTrace(SightDistance, -SightAngle);
	ImpactMiddle = LineTrace(SightDistance, 0.0f);
	ImpactRight = LineTrace(SightDistance, SightAngle);

	InputsToNeuralNetwork.Empty();

	InputsToNeuralNetwork.Add(ImpactLeft);
	InputsToNeuralNetwork.Add(ImpactMiddle);
	InputsToNeuralNetwork.Add(ImpactRight);

	Network->ForwardPropagation(InputsToNeuralNetwork);

	Network->GetResults(Results);

	GetPawn()->AddMovementInput(FRotationMatrix(FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f)).GetScaledAxis(EAxis::X), Results[0], false);
	GetPawn()->SetActorRotation(FRotator(GetPawn()->GetActorRotation().Pitch, GetPawn()->GetActorRotation().Yaw + (Results[1] * 2 - 1), GetPawn()->GetActorRotation().Roll));

	if (IncomingIsLearning)
	{
		IdealOutputsForNeuralNetwork.Empty();
		bLeftOutput = ImpactLeft == -1.0f ? true : false;
		bMiddleOutput = ImpactMiddle == -1.0f ? true : false;
		bRightOutput = ImpactRight == -1.0f ? true : false;
		bTotalOutput = bLeftOutput && bMiddleOutput && bRightOutput;

		IdealOutputsForNeuralNetwork.Add(bTotalOutput ? 1.0f : 0.1f);
		//IdealOutputsForNeuralNetwork.Add(ImpactLeft == -1.0f ? true : false && ImpactMiddle == -1.0f ? true : false && ImpactRight == -1.0f ? true : false ? 1.0f : 0.1f);

		
		LeftTurnValue = ImpactLeft == -1.0f ? 0.5f : 1.0f;
		RightTurnValue = ImpactRight == -1.0f ? LeftTurnValue : 0.0f;

		IdealOutputsForNeuralNetwork.Add(RightTurnValue);
		//IdealOutputsForNeuralNetwork.Add(ImpactRight == -1.0f ? ImpactLeft == -1.0f ? 0.5f : 1.0f : 0.0f);

		Network->BackwardPropagationOfErrors(IdealOutputsForNeuralNetwork);
	}
}
