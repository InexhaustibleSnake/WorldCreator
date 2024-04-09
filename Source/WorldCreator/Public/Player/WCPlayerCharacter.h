// The project was made for a technical assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WCPlayerCharacter.generated.h"

class UCameraComponent;

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UCameraComponent* MainCamera;
};
