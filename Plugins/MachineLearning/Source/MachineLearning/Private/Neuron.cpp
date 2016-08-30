// Robert Chubb - Saxon Rah - Parabolic Labs
// Neuron UObject

#include "MachineLearningPrivatePCH.h"

#include <cmath>
#include <algorithm>

#include "Neuron.h"

float UNeuron::TotalTheErrorContribution(const TArray<UNeuron*> &NextLayer) const
{
	float Total = 0.0;
	// Total Error Contribution from the neurons we give
	for (int32 i = 0; i < NextLayer.Num() - 1; ++i)
	{
		Total += OutputWeights[i].Weight * NextLayer[i]->Gradient;
	}
	return Total;
}

float UNeuron::TransferTanh(float IncomingValue)
{
	// tanh - output range [-1.0..1.0]
	return std::tanh(IncomingValue);
}

float UNeuron::TransferDerivativeTanh(float IncomingValue)
{
	// tanh derivative
	return 1.0 - IncomingValue * IncomingValue;
}

float UNeuron::TransferLogistic(float x)
{
	return 1.0f / (1.0f + std::exp(-x));
	//return 1.0f / (1.0f + FMath::Exp(-x));
}
float UNeuron::TransferDerivativeLogistic(float x)
{
	return std::exp(-x) / std::pow((std::exp(-x) + 1.0f), 2.0f);
	//return FMath::Exp(-x) / FMath::Pow((FMath::Exp(-x) + 1.0f), 2.0f);
}

// ramp is a constant slope between -1 <= x <= 1, zero slope elsewhere; output ranges from -1 to +1:
float UNeuron::TransferRamp(float x)
{
	if (x < -1.0) return -1.0;
	else if (x > 1.0) return 1.0;
	else return x;
}
float UNeuron::TransferDerivativeRamp(float x)
{
	return (x < -1.0f || x > 1.0f) ? 0.0f : 1.0f;
}

// Gaussian: Bell Curve Function
float UNeuron::TransferGaussian(float x)
{
	return std::exp(-((x * x) / 2.0f));
	//return FMath::Exp(-((x * x) / 2.0f));
}
float UNeuron::TransferDerivativeGaussian(float x)
{
	return -x * std::exp(-(x * x) / 2.0f);
	//return -x * FMath::Exp(-(x * x) / 2.0f);
}

// SoftPlus
float UNeuron::TransferSoftPlus(float x)
{
	return std::max(0.0f, x);
}
float UNeuron::TransferDerivativeSoftPlus(float x)
{
	return TransferLogistic(x);
}

float UNeuron::GetRandomWeight()
{
	return FMath::FRand() / float(RAND_MAX);
}

void UNeuron::Setup(int32 NumberOfOutputs, int32 IncomingIndex, ETransferType IncomingTransferType, float IncomingNetRate, float IncomingNetMomentum)
{
	NeuronTrainingRate = IncomingNetRate;
	NeuronMomentum = IncomingNetMomentum;
	NeuronTransferType = IncomingTransferType;
	for (int32 i = 0; i < NumberOfOutputs; ++i)
	{
		OutputWeights.Add(Connection());
		OutputWeights.Last().Weight = GetRandomWeight();
	}
	Index = IncomingIndex;
}

void UNeuron::SetOutput(float IncomingValue)
{
	Output = IncomingValue;
}

float UNeuron::GetOutput() const
{ 
	return Output; 
}

void UNeuron::FeedForward(const TArray<UNeuron*> &PreviousLayer)
{
	float Total = 0.0;
	// Total the previous layer's outputs (which are our inputs) We include the bias neuron from the previous layer.
	for (int32 i = 0; i < PreviousLayer.Num(); ++i)
	{
		Total += PreviousLayer[i]->GetOutput() * PreviousLayer[i]->OutputWeights[Index].Weight;
	}
	
	switch (NeuronTransferType)
	{
	case ETransferType::TT_Ramp:
		Output = UNeuron::TransferRamp(Total);
		break;
	case ETransferType::TT_Gaussian:
		Output = UNeuron::TransferGaussian(Total);
		break;
	case ETransferType::TT_Tanh:
		Output = UNeuron::TransferTanh(Total);
		break;
	case ETransferType::TT_Logistic:
		Output = UNeuron::TransferLogistic(Total);
		break;
	case ETransferType::TT_SoftPlus:
		Output = UNeuron::TransferSoftPlus(Total);
		break;
	default:
		Output = UNeuron::TransferTanh(Total);
		break;
	}
	
}

void UNeuron::CalculateOutputGradients(float IncomingValue)
{
	float Delta = IncomingValue - Output;

	switch (NeuronTransferType)
	{
	case ETransferType::TT_Ramp:
		Gradient = Delta * UNeuron::TransferDerivativeRamp(Output);
		break;
	case ETransferType::TT_Gaussian:
		Gradient = Delta * UNeuron::TransferDerivativeGaussian(Output);
		break;
	case ETransferType::TT_Tanh:
		Gradient = Delta * UNeuron::TransferDerivativeTanh(Output);
		break;
	case ETransferType::TT_Logistic:
		Gradient = Delta * UNeuron::TransferDerivativeLogistic(Output);
		break;
	case ETransferType::TT_SoftPlus:
		Gradient = Delta * UNeuron::TransferDerivativeSoftPlus(Output);
		break;
	default:
		Gradient = Delta * UNeuron::TransferDerivativeTanh(Output);
		break;
	}
}

void UNeuron::CalculateHiddenGradients(const TArray<UNeuron*> &NextLayer)
{
	float Total = TotalTheErrorContribution(NextLayer);
	switch (NeuronTransferType)
	{
	case ETransferType::TT_Ramp:
		Gradient = Total * UNeuron::TransferDerivativeRamp(Output);
		break;
	case ETransferType::TT_Gaussian:
		Gradient = Total * UNeuron::TransferDerivativeGaussian(Output);
		break;
	case ETransferType::TT_Tanh:
		Gradient = Total * UNeuron::TransferDerivativeTanh(Output);
		break;
	case ETransferType::TT_Logistic:
		Gradient = Total * UNeuron::TransferDerivativeLogistic(Output);
		break;
	case ETransferType::TT_SoftPlus:
		Gradient = Total * UNeuron::TransferDerivativeSoftPlus(Output);
		break;
	default:
		Gradient = Total * UNeuron::TransferDerivativeTanh(Output);
		break;
	}
}

void UNeuron::UpdateInputWeights(TArray<UNeuron*> &PreviousLayer)
{
	// The weights that will be updated are in the Connection container in the neurons in the preceding layer

	for (int32 i = 0; i < PreviousLayer.Num(); ++i)
	{
		UNeuron &Neuron = *PreviousLayer[i];
		float OldDeltaWeight = Neuron.OutputWeights[Index].DeltaWeight;
		// Individual input multiplied by the gradient and training rate, add momentum by a fraction of the previous delta weight;
		float NewDeltaWeight = NeuronTrainingRate * Neuron.GetOutput() * Gradient + NeuronMomentum * OldDeltaWeight;
		// Update Weights
		Neuron.OutputWeights[Index].DeltaWeight = NewDeltaWeight;
		Neuron.OutputWeights[Index].Weight += NewDeltaWeight;
	}
}
