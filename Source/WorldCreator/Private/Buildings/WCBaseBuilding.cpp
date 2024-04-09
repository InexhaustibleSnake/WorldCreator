// The project was made for a technical assignment

#include "Buildings/WCBaseBuilding.h"
#include "Components/TextRenderComponent.h"

AWCBaseBuilding::AWCBaseBuilding()
{
    PrimaryActorTick.bCanEverTick = false;

    BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
    BuildingMesh->SetGenerateOverlapEvents(false);
    SetRootComponent(BuildingMesh);

    ResourcesAmountText = CreateDefaultSubobject<UTextRenderComponent>("ResourcesAmountText");
    ResourcesAmountText->SetupAttachment(GetRootComponent());

    ResourcesAmountText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AWCBaseBuilding::BeginPlay()
{
    Super::BeginPlay();

    SetResourcesText(FText::FromString(FString::SanitizeFloat(Resources)));
}

void AWCBaseBuilding::SetResourcesText(const FText& Text)
{
    if (!ResourcesAmountText) return;

    ResourcesAmountText->SetText(Text);
}

void AWCBaseBuilding::SetResources(float Amount)
{
    Resources = Amount;

    SetResourcesText(FText::FromString(FString::SanitizeFloat(Resources)));
}

void AWCBaseBuilding::RemoveResources(float Amount)
{
    float FinalResources = FMath::Clamp(Resources - Amount, 0.0f, MaxResources);
    SetResources(FinalResources);
}

void AWCBaseBuilding::AddResources(float Amount)
{
    float FinalResources = FMath::Clamp(Resources + Amount, 0.0f, MaxResources);
    SetResources(FinalResources);
}