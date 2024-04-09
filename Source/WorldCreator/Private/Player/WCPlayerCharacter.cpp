// The project was made for a technical assignment

#include "Player/WCPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Buildings/WCBaseBuilding.h"
#include "Buildings/WCSourceBuilding.h"

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

    for (const auto& OneAction : PlayerBuildActionsData)  // This is where we bind the building inputs
    {
        FInputActionBinding ActionBinding(OneAction.Key, IE_Pressed);  // This is necessary to comply with the DRY principle
        ActionBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([&, OneAction]() { CreateBuilding(OneAction.Value); });
        PlayerInputComponent->AddActionBinding(ActionBinding);
    }
}

void AWCPlayerCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AWCPlayerCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void AWCPlayerCharacter::CreateBuilding(const TSubclassOf<AWCBaseBuilding>& BuildingClass)
{
    if (!BuildingClass) return;

    FVector TraceStart;

    FRotator TraceRotation;

    if (!GetPlayerViewPoint(TraceStart, TraceRotation)) return;

    FHitResult HitResult;

    MakeTrace(TraceStart, TraceRotation, HitResult);

    if (HitResult.bBlockingHit && GetWorld())
    {
        FActorSpawnParameters BuildingSpawnParameters;

        GetWorld()->SpawnActor<AWCBaseBuilding>(BuildingClass, HitResult.ImpactPoint, FRotator::ZeroRotator, BuildingSpawnParameters);
    }
}

void AWCPlayerCharacter::MakeTrace(const FVector& ViewLocation, const FRotator& ViewRotation, FHitResult& HitResult)
{
    FVector TraceEnd = ViewRotation.Vector() * SpawnTraceDistance + ViewLocation;

    if (!GetWorld()) return;

    GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECollisionChannel::ECC_Visibility);
}

bool AWCPlayerCharacter::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (!PlayerController) return false;

    PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

    return true;
}
