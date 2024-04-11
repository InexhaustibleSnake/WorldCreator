// The project was made for a technical assignment

#include "Player/WCLevelManagerComponent.h"
#include "Buildings/WCBaseBuilding.h"
#include "EngineUtils.h"

UWCLevelManagerComponent::UWCLevelManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWCLevelManagerComponent::NextLevel()
{
    SaveLevelData(CurrentLevelIndex);

    UnloadAllBuildingsInLevel(CurrentLevelIndex);

    SetCurrentLevelIndex(++CurrentLevelIndex);

    LoadAllBuildingsInLevel(CurrentLevelIndex);
}

void UWCLevelManagerComponent::PreviousLevel()
{
    SaveLevelData(CurrentLevelIndex);

    UnloadAllBuildingsInLevel(CurrentLevelIndex);

    SetCurrentLevelIndex(--CurrentLevelIndex);

    LoadAllBuildingsInLevel(CurrentLevelIndex);
}

void UWCLevelManagerComponent::SaveLevelData(int32 LevelIndex)
{
    if (!GetWorld()) return;

    TArray<AWCBaseBuilding*> FoundBuildings;

    for (TActorIterator<AWCBaseBuilding> OneBuilding(GetWorld()); OneBuilding; ++OneBuilding)
    {
        if (!*OneBuilding || !OneBuilding->GetIsLoaded()) continue;

        FoundBuildings.Add(*OneBuilding);
    }

    if (LevelsData.IsValidIndex(LevelIndex))
    {
        LevelsData[LevelIndex].SetBuildingsInLevel(FoundBuildings);
    }
    else
    {
        FBuildings Buildings;
        Buildings.SetBuildingsInLevel(FoundBuildings);
        LevelsData.Add(Buildings);
    }
}

void UWCLevelManagerComponent::LoadAllBuildingsInLevel(int32 LevelIndex)
{
    if (!GetWorld() || !LevelsData.IsValidIndex(LevelIndex)) return;

    for (auto OneBuilding : LevelsData[LevelIndex].GetBuildingsInLevel())
    {
        if (!OneBuilding || OneBuilding->GetIsLoaded()) continue;

        OneBuilding->SetActorHiddenInGame(false);
        OneBuilding->SetIsLoaded(true);
        OneBuilding->SetActorEnableCollision(true);
    }
}

void UWCLevelManagerComponent::UnloadAllBuildingsInLevel(int32 LevelIndex)
{
    if (!GetWorld() || !LevelsData.IsValidIndex(LevelIndex)) return;

    for (auto OneBuilding : LevelsData[LevelIndex].GetBuildingsInLevel())
    {
        if (!OneBuilding || !OneBuilding->GetIsLoaded()) continue;

        OneBuilding->SetActorHiddenInGame(true);
        OneBuilding->SetIsLoaded(false);
        OneBuilding->SetActorEnableCollision(false);
    }
}

void UWCLevelManagerComponent::SetLevelData(int32 LevelIndex, const FBuildings& Buildings)
{
    LevelsData[LevelIndex] = Buildings;
}

void UWCLevelManagerComponent::SetCurrentLevelIndex(int32 Index)
{
    CurrentLevelIndex = FMath::Clamp(Index, 0, LevelsData.Num());
    OnLevelIndexChanged.Broadcast(CurrentLevelIndex);
}
