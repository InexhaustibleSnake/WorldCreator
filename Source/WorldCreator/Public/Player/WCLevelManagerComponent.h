// The project was made for a technical assignment

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WCLevelManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelIndexChanged, int32, NewLevelIndex);

class AWCBaseBuilding;

USTRUCT(BlueprintType)
struct FBuildings
{
    GENERATED_USTRUCT_BODY()

public:
    void SetBuildingsInLevel(TArray<AWCBaseBuilding*> Buildings) { BuildingsInLevel = Buildings; }
    TArray<AWCBaseBuilding*> GetBuildingsInLevel() const { return BuildingsInLevel; }

private:
    UPROPERTY()
    TArray<AWCBaseBuilding*> BuildingsInLevel;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WORLDCREATOR_API UWCLevelManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UWCLevelManagerComponent();

    void NextLevel();
    void PreviousLevel();

    UPROPERTY(BlueprintAssignable) 
    FOnLevelIndexChanged OnLevelIndexChanged;

protected:
    void SaveLevelData(int32 LevelIndex);

    void LoadAllBuildingsInLevel(int32 LevelIndex);
    void UnloadAllBuildingsInLevel(int32 LevelIndex);

    void SetLevelData(int32 LevelIndex, const FBuildings& Buildings);

    void SetCurrentLevelIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Level Manager Component")
    int32 GetCurrentLevelIndex() const { return CurrentLevelIndex; }

    UPROPERTY()
    int32 CurrentLevelIndex = 0;

    UPROPERTY()
    TArray<FBuildings>LevelsData;
};
