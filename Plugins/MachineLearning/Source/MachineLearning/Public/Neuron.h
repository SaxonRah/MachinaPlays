// Robert Chubb - Saxon Rah - Parabolic Labs
// Neuron UObject
#pragma once

#include "Neuron.generated.h"

template <typename TempObjType>
static FORCEINLINE TempObjType* SpawnBP(
	UWorld*         TheWorld,
	UClass*         TheBP,
	const FVector&  Loc,
	const FRotator& Rot,
	const ESpawnActorCollisionHandlingMethod CollisionHandle = ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
	AActor*         Owner = NULL,
	APawn*          Instigator = NULL
) {
	if (!TheWorld) return NULL;
	if (!TheBP) return NULL;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = CollisionHandle;
	SpawnInfo.Owner = Owner;
	SpawnInfo.Instigator = Instigator;
	SpawnInfo.bDeferConstruction = false;

	return TheWorld->SpawnActor<TempObjType>(TheBP, Loc, Rot, SpawnInfo);
}

struct Connection
{
	float Weight;
	float DeltaWeight;
};

UENUM(BlueprintType)
enum class ETransferType : uint8
{
	TT_Ramp						UMETA(DisplayName = "Ramp"),
	TT_Gaussian					UMETA(DisplayName = "Gaussian"),
	TT_Tanh						UMETA(DisplayName = "Tanh"),
	TT_Logistic					UMETA(DisplayName = "Logistic"),
	TT_SoftPlus					UMETA(DisplayName = "SoftPlus")

};

UCLASS(Blueprintable)
class UNeuron : public UObject
{
	GENERATED_BODY()

	float Output;
	TArray<Connection> OutputWeights;
	int32 Index;
	float Gradient;

	float TotalTheErrorContribution(const TArray<UNeuron*> &NextLayer) const;

	static float GetRandomWeight();

	// Transfer Functions
	// tanh is a sigmoid curve scaled; output ranges from -1 to +1:
	static float TransferTanh(float IncomingValue);
	static float TransferDerivativeTanh(float IncomingValue);

	// logistic is a sigmoid curve that ranges 0.0 to 1.0:
	float TransferLogistic(float x);
	float TransferDerivativeLogistic(float x);

	// ramp is a constant slope between -1 <= x <= 1, zero slope elsewhere; output ranges from -1 to +1:
	float TransferRamp(float x);
	float TransferDerivativeRamp(float x);

	// Gaussian:
	float TransferGaussian(float x);
	float TransferDerivativeGaussian(float x);

	// SoftPlus:
	float TransferSoftPlus(float x);
	float TransferDerivativeSoftPlus(float x);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
		ETransferType NeuronTransferType = ETransferType::TT_Tanh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
		float NeuronTrainingRate = 0.15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
		float NeuronMomentum = 0.5;

	UNeuron()
	{};

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void Setup(int32 NumberOfOutputs, int32 IncomingIndex, ETransferType IncomingTransferType, float IncomingNetRate, float IncomingNetMomentum);

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void SetOutput(float IncomingValue);

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		float GetOutput() const;

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void FeedForward(const TArray<UNeuron*> &PreviousLayer);

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void CalculateOutputGradients(float IncomingValue);

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void CalculateHiddenGradients(const TArray<UNeuron*> &NextLayer);

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void UpdateInputWeights(TArray<UNeuron*> &PreviousLayer);
};
