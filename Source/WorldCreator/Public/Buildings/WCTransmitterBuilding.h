// The project was made for a technical assignment

#pragma once

#include "CoreMinimal.h"
#include "Buildings/WCSourceBuilding.h"
#include "WCTransmitterBuilding.generated.h"

UCLASS()
class WORLDCREATOR_API AWCTransmitterBuilding : public AWCBaseBuilding
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Transmitter")
    AWCBaseBuilding* GetNearestBuilding(const TSubclassOf<AWCBaseBuilding>& BuildingClass) const;

    UFUNCTION(BlueprintCallable, Category = "Transmitter")
    void SetTargetGBuilding(AWCBaseBuilding* Building) { TargetBuilding = Building; }

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void TakeResourcesFromBuilding(float Amount, AWCBaseBuilding* TargetBuildingReference);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Transmitter", meta = (ClampMin = "0.1", ClampMax = "1000000.0"))
    float ResourcesToTakeAmount = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Transmitter", meta = (ClampMin = "0.1", ClampMax = "1000000.0"))
    float ResourcesToTakeRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Transmitter")
    TSubclassOf<AWCBaseBuilding> TargetBuildingClass = AWCBaseBuilding::StaticClass();

    UPROPERTY()
    AWCBaseBuilding* TargetBuilding;

    FTimerHandle BuildingTimer;
    FTimerDelegate BuildingTimerDelegate;
};
