// The project was made for a technical assignment

#include "Player/WCPlayerCharacter.h"
#include "Camera/CameraComponent.h"

AWCPlayerCharacter::AWCPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
    MainCamera->SetupAttachment(GetRootComponent());

    bUseControllerRotationPitch = true;
}

void AWCPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    ensure(MainCamera);
}

void AWCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (!PlayerInputComponent) return;

    PlayerInputComponent->BindAxis("MoveForward", this, &AWCPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AWCPlayerCharacter::MoveRight);

    PlayerInputComponent->BindAxis("MouseY", this, &AWCPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("MouseX", this, &AWCPlayerCharacter::AddControllerYawInput);
}

void AWCPlayerCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AWCPlayerCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}