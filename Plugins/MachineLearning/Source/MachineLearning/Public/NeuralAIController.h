// Robert Chubb - Saxon Rah - Parabolic Labs
// Neural AIController
#pragma once
#include "AIController.h"
#include "NeuralNet.h"
#include "NeuralAIController.generated.h"

UCLASS()
class ANeuralAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		float SightAngle = 35.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		float SightDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		UClass* NetToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		ANeuralNet* Network;

	TArray<float> InputsToNeuralNetwork;
	TArray<float> IdealOutputsForNeuralNetwork;
	TArray<float> Results;

	bool bLeftOutput = false;
	bool bMiddleOutput = false;
	bool bRightOutput = false;

	bool bTotalOutput = false;

	float ImpactLeft = 0.0f;
	float ImpactMiddle = 0.0f;
	float ImpactRight = 0.0f;

	float LeftTurnValue = 0.0f;
	float RightTurnValue = 0.0f;

	ANeuralAIController()
	{};

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool LineTraceSingle_NEW(UObject* WorldContextObject, const FVector Start, const FVector End, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor);

	bool LineTraceSingle_DEPRECATED(UObject* WorldContextObject, const FVector Start, const FVector End, ECollisionChannel TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor);

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		float LineTrace(float IncomingSightDistance, float IncomingAngle);

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void Simulate(bool IncomingIsLearning);

};
