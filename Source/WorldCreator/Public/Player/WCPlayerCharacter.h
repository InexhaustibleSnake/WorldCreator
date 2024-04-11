// The project was made for a technical assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WCPlayerCharacter.generated.h"

class UCameraComponent;
class AWCBaseBuilding;
class UWCLevelManagerComponent;

UCLASS()
class WORLDCREATOR_API AWCPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AWCPlayerCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void CreateBuilding(const TSubclassOf<AWCBaseBuilding>& BuildingClass);

    void MakeTrace(const FVector& ViewLocation, const FRotator& ViewRotation, FHitResult& HitResult);

    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);

    void NextLevel();
    void PreviousLevel();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UCameraComponent* MainCamera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UWCLevelManagerComponent* WCLevelManagerComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WCPlayerCharacter")
    TMap<FName, TSubclassOf<AWCBaseBuilding>> PlayerBuildActionsData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WCPlayerCharacter")
    float SpawnTraceDistance = 2000.0f;
};
