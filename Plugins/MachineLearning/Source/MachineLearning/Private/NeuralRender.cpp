// Robert Chubb - Saxon Rah - Parabolic Labs
// Neural Render Actor

#include "MachineLearningPrivatePCH.h"
#include "NeuralRender.h"

// Pixel Bit offset
#define BLUE 0
#define GREEN 1
#define RED 2
#define ALPHA 3
#define ALPHA_CHECK 200

void UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData)
{
	if (Texture && Texture->Resource)
	{
		struct FUpdateTextureRegionsData
		{
			FTexture2DResource* Texture2DResource;
			int32 MipIndex;
			uint32 NumRegions;
			FUpdateTextureRegion2D* Regions;
			uint32 SrcPitch;
			uint32 SrcBpp;
			uint8* SrcData;
		};

		FUpdateTextureRegionsData* RegionData = new FUpdateTextureRegionsData;

		RegionData->Texture2DResource = (FTexture2DResource*)Texture->Resource;
		RegionData->MipIndex = MipIndex;
		RegionData->NumRegions = NumRegions;
		RegionData->Regions = Regions;
		RegionData->SrcPitch = SrcPitch;
		RegionData->SrcBpp = SrcBpp;
		RegionData->SrcData = SrcData;

		ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
			UpdateTextureRegionsData,
			FUpdateTextureRegionsData*, RegionData, RegionData,
			bool, bFreeData, bFreeData,
			{
				for (uint32 RegionIndex = 0; RegionIndex < RegionData->NumRegions; ++RegionIndex)
				{
					int32 CurrentFirstMip = RegionData->Texture2DResource->GetCurrentFirstMip();
					if (RegionData->MipIndex >= CurrentFirstMip)
					{
						RHIUpdateTexture2D(
							RegionData->Texture2DResource->GetTexture2DRHI(),
							RegionData->MipIndex - CurrentFirstMip,
							RegionData->Regions[RegionIndex],
							RegionData->SrcPitch,
							RegionData->SrcData
							+ RegionData->Regions[RegionIndex].SrcY * RegionData->SrcPitch
							+ RegionData->Regions[RegionIndex].SrcX * RegionData->SrcBpp
							);
					}
				}
				if (bFreeData)
				{
					FMemory::Free(RegionData->Regions);
					FMemory::Free(RegionData->SrcData);
				}
				delete RegionData;
			});
	}
}

ANeuralRender::ANeuralRender(const class FObjectInitializer& PCIP)
{
	PrimaryActorTick.bCanEverTick = true;


	mDynamicColors = nullptr;
	mUpdateTextureRegion = nullptr;
}

void ANeuralRender::BeginPlay()
{
	Super::BeginPlay();


	SetupTexture();
}

void ANeuralRender::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	delete[] mDynamicColors; mDynamicColors = nullptr;
	delete mUpdateTextureRegion; mUpdateTextureRegion = nullptr;

	Super::EndPlay(EndPlayReason);
}

void ANeuralRender::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetupTexture();
}

void ANeuralRender::SetupTexture()
{
	if (mDynamicColors) delete[] mDynamicColors;
	if (mUpdateTextureRegion) delete mUpdateTextureRegion;

	int32 w, h;
	// Size of material
	w = 256;
	h = w;

	mDynamicMaterials.Empty();
	mDynamicMaterials.Add(GetStaticMeshComponent()->CreateAndSetMaterialInstanceDynamic(0));
	mDynamicTexture = UTexture2D::CreateTransient(w, h);
	mDynamicTexture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	mDynamicTexture->SRGB = 0;
	mDynamicTexture->Filter = TextureFilter::TF_Nearest;
	mDynamicTexture->AddToRoot();
	mDynamicTexture->UpdateResource();

	mUpdateTextureRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, w, h);

	mDynamicMaterials[0]->SetTextureParameterValue("DynamicTextureParam", mDynamicTexture);

	mDataSize = w * h * 4;
	mDataSqrtSize = w * 4;
	mArraySize = w * h;
	mArrayRowSize = w;

	mDynamicColors = new uint8[mDataSize];

	memset(mDynamicColors, 0, mDataSize);
}

void ANeuralRender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (uint32 i = 0; i < mArraySize; ++i)
	{
		uint32 x = i % mArrayRowSize;
		uint32 y = i / mArrayRowSize;

		bool state = FMath::RandBool();

		mDynamicColors[i * 4 + RED] = state ? 0xFF : 0x00;
	}

	UpdateTexture();
}

void ANeuralRender::UpdateTexture()
{
	UpdateTextureRegions(mDynamicTexture, 0, 1, mUpdateTextureRegion, mDataSqrtSize, (uint32)4, mDynamicColors, false);
	mDynamicMaterials[0]->SetTextureParameterValue("DynamicTextureParam", mDynamicTexture);
}
