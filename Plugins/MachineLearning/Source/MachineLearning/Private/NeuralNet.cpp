// Robert Chubb - Saxon Rah - Parabolic Labs
// Neural Net UObject

#include "MachineLearningPrivatePCH.h"
#include <cmath>
#include "NeuralNet.h"

void ANeuralNet::Setup(const TArray<int32> &NeurologicalMap, ETransferType IncomingTransferType, float IncomingTrainingRate, float IncomingMomentum)
{
	int32 NumberOfLayers = NeurologicalMap.Num();
	for (int32 CurrentLayerNumer = 0; CurrentLayerNumer < NumberOfLayers; ++CurrentLayerNumer)
	{
		NeurologicalLayers.Add(TArray<UNeuron*>());
		int32 NumberOfOutputs = CurrentLayerNumer == NeurologicalMap.Num() - 1 ? 0 : NeurologicalMap[CurrentLayerNumer + 1];
		// New neurological map layer, fill it with neurons. Add the bias neuron for each layer. (<=* number of neurons + single bias)
		for (int32 CurrentNeuronNumber = 0; CurrentNeuronNumber <= NeurologicalMap[CurrentLayerNumer]; ++CurrentNeuronNumber)
		{
			UNeuron* temp = NewObject<UNeuron>(UNeuron::StaticClass());
			//UNeuron* temp = ConstructObject<UNeuron>(UNeuron::StaticClass());
			temp->AddToRoot();
			temp->Setup(NumberOfOutputs, CurrentNeuronNumber, IncomingTransferType, IncomingTrainingRate, IncomingMomentum);
			NeurologicalLayers.Last().Add(temp);
		}
		// Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
		NeurologicalLayers.Last().Last()->SetOutput(1.0);
	}
}

void ANeuralNet::ForwardPropagation(const TArray<float> &InputFloatArray)
{
	ensure(InputFloatArray.Num() == NeurologicalLayers[0].Num() - 1);
	// Assign (latch) the input values into the input neurons
	for (int32 i = 0; i < InputFloatArray.Num(); ++i)
	{
		NeurologicalLayers[0][i]->SetOutput(InputFloatArray[i]);
	}
	// forward propagate
	for (int32 CurrentLayerNumber = 1; CurrentLayerNumber < NeurologicalLayers.Num(); ++CurrentLayerNumber)
	{
		TArray<UNeuron*> &PreviousLayer = NeurologicalLayers[CurrentLayerNumber - 1];
		for (int32 i = 0; i < NeurologicalLayers[CurrentLayerNumber].Num() - 1; ++i)
		{
			NeurologicalLayers[CurrentLayerNumber][i]->FeedForward(PreviousLayer);
		}
	}
}

void ANeuralNet::BackwardPropagationOfErrors(const TArray<float> &InputFloatArray)
{
	// Calculate overall UNeuralNet error (Root Mean Square of output neuron errors)
	TArray<UNeuron*> &OutputLayer = NeurologicalLayers.Last();
	Error = 0.0;

	for (int32 i = 0; i < OutputLayer.Num() - 1; ++i) 
	{
		float Delta = InputFloatArray[i] - OutputLayer[i]->GetOutput();
		Error += Delta * Delta;
	}
	// Get average error squared
	Error /= OutputLayer.Num() - 1;
	// Root Mean Square
	//Error = std::sqrt(Error);
	Error = FMath::Sqrt(Error);
	 // Implement a recent average measurement
	RecentAverageError = (RecentAverageError * RecentAverageSmoothingFactor + Error) / (RecentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients
	for (int32 i = 0; i < OutputLayer.Num() - 1; ++i)
	{
		OutputLayer[i]->CalculateOutputGradients(InputFloatArray[i]);
	}

	// Calculate hidden layer gradients
	for (int32 CurrentLayerNumber = NeurologicalLayers.Num() - 2; CurrentLayerNumber > 0; --CurrentLayerNumber)
	{
		TArray<UNeuron*> &HiddenLayer = NeurologicalLayers[CurrentLayerNumber];
		TArray<UNeuron*> &NextLayer = NeurologicalLayers[CurrentLayerNumber + 1];

		for (int32 i = 0; i < HiddenLayer.Num(); ++i)
		{
			HiddenLayer[i]->CalculateHiddenGradients(NextLayer);
		}
	}

	// For all layers from outputs to first hidden layer,
	// update connection weights
	for (int32 CurrentLayerNumber = NeurologicalLayers.Num() - 1; CurrentLayerNumber > 0; --CurrentLayerNumber)
	{
		TArray<UNeuron*> &CurrentLayer = NeurologicalLayers[CurrentLayerNumber];
		TArray<UNeuron*> &PreviousLayer = NeurologicalLayers[CurrentLayerNumber - 1];

		for (int32 i = 0; i < CurrentLayer.Num() - 1; ++i)
		{
			CurrentLayer[i]->UpdateInputWeights(PreviousLayer);
		}
	}
}

void ANeuralNet::GetResults(TArray<float> &ResultFloatArray) const
{
	ResultFloatArray.Empty();

	for (int32 i = 0; i < NeurologicalLayers.Last().Num() - 1; ++i)
	{
		ResultFloatArray.Add(NeurologicalLayers.Last()[i]->GetOutput());
	}
}

float ANeuralNet::GetRecentAverageError() const
{
	return RecentAverageError;
}
