// The project was made for a technical assignment

#include "Buildings/WCTransmitterBuilding.h"
#include "EngineUtils.h"

void AWCTransmitterBuilding::BeginPlay()
{
    Super::BeginPlay();

    TargetBuilding = GetNearestBuilding(TargetBuildingClass);

    BuildingTimerDelegate.BindUFunction(this, FName("TakeResourcesFromBuilding"), ResourcesToTakeAmount, TargetBuilding);
    GetWorldTimerManager().SetTimer(BuildingTimer, BuildingTimerDelegate, ResourcesToTakeRate, true);
}

AWCBaseBuilding* AWCTransmitterBuilding::GetNearestBuilding(const TSubclassOf<AWCBaseBuilding>& BuildingClass) const
{
    AWCBaseBuilding* NearestBuilding = nullptr;

    float DistanceFromNearestActor = TNumericLimits<float>::Max();

    for (TActorIterator<AWCBaseBuilding> OneBuilding(GetWorld()); OneBuilding; ++OneBuilding)
    {
        if (!*OneBuilding || *OneBuilding == this|| !OneBuilding->GetIsLoaded()) continue;

        const float DistanceFromActorToCheck = (GetActorLocation() - OneBuilding->GetActorLocation()).SizeSquared();
        if (DistanceFromActorToCheck < DistanceFromNearestActor)
        {
            NearestBuilding = *OneBuilding;
            DistanceFromNearestActor = DistanceFromActorToCheck;
        }
    }

    return NearestBuilding;
}

void AWCTransmitterBuilding::TakeResourcesFromBuilding(float Amount, AWCBaseBuilding* TargetBuildingReference)
{
    if (!TargetBuilding)
    {
        GetWorldTimerManager().ClearTimer(BuildingTimer);
        return;
    }

    float TargetBuildingResources = TargetBuilding->GetResourcesAmount();

    if (FMath::IsNearlyZero(TargetBuildingResources))
    {
        GetWorldTimerManager().ClearTimer(BuildingTimer);
        return;
    }

    AddResources(ResourcesToTakeAmount);
    TargetBuilding->RemoveResources(ResourcesToTakeAmount);
}
