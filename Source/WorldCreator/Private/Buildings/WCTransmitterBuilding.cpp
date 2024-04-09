// The project was made for a technical assignment

#include "Buildings/WCTransmitterBuilding.h"
#include "Kismet/GameplayStatics.h"

void AWCTransmitterBuilding::BeginPlay()
{
    Super::BeginPlay();

    TargetBuilding = GetNearestBuilding(TargetBuildingClass);

    BuildingTimerDelegate.BindUFunction(this, FName("TakeResourcesFromBuilding"), ResourcesToTakeAmount, TargetBuilding);
    GetWorldTimerManager().SetTimer(BuildingTimer, BuildingTimerDelegate, ResourcesToTakeRate, true);
}

AWCBaseBuilding* AWCTransmitterBuilding::GetNearestBuilding(const TSubclassOf<AWCBaseBuilding>& BuildingClass) const
{
    TArray<AActor*> FoundActors;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), BuildingClass, FoundActors);

    float Distance = 0.0f;

    return Cast<AWCBaseBuilding>(UGameplayStatics::FindNearestActor(GetActorLocation(), FoundActors, Distance));
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
