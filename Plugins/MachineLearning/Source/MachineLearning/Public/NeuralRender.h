// Robert Chubb - Saxon Rah - Parabolic Labs
// Neural Render Actor

#pragma once
#include "Engine/StaticMeshActor.h"

#include "NeuralNet.h"

#include "NeuralRender.generated.h"

UCLASS()
class ANeuralRender : public AStaticMeshActor
{
	GENERATED_BODY()
public:

	/** NeuralRender **/
	ANeuralRender(const class FObjectInitializer& PCIP);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaTime) override;

	void SetupTexture();
	void UpdateTexture();

	TArray<class UMaterialInstanceDynamic*> mDynamicMaterials;
	FUpdateTextureRegion2D* mUpdateTextureRegion;
	UTexture2D* mDynamicTexture;

	uint8* mDynamicColors;
	uint32 mDataSize;
	uint32 mDataSqrtSize;
	uint32 mArraySize;
	uint32 mArrayRowSize;
	/** NeuralRender **/
};



