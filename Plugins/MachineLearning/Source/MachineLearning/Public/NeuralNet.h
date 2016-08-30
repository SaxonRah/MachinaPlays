// Robert Chubb - Saxon Rah - Parabolic Labs
// NeuralNet UObject
#pragma once

#include "Neuron.h"
#include "NeuralNet.generated.h"

UCLASS(Blueprintable)
class ANeuralNet : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		ETransferType TransferType = ETransferType::TT_Tanh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		float RecentAverageSmoothingFactor = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		float NetTrainingRate = 0.15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "NeuralNetwork")
		float NetMomentum = 0.5;

	TArray<TArray<UNeuron*>> NeurologicalLayers; // m_layers[layerNum][neuronNum]
	float Error;
	float RecentAverageError;

	ANeuralNet()
	{};

	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void Setup(const TArray<int32> &NeurologicalMap, ETransferType IncomingTransferType, float IncomingTrainingRate, float IncomingMomentum);
	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void ForwardPropagation(const TArray<float> &InputFloatArray);
	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void BackwardPropagationOfErrors(const TArray<float> &InputFloatArray);
	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		void GetResults(TArray<float> &ResultFloatArray) const;
	UFUNCTION(BlueprintCallable, Category = "NeuralNetwork")
		float GetRecentAverageError() const;
};
