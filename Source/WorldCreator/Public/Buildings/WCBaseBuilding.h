// The project was made for a technical assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WCBaseBuilding.generated.h"

class UTextRenderComponent;

UCLASS()
class WORLDCREATOR_API AWCBaseBuilding : public AActor
{
    GENERATED_BODY()

public:
    AWCBaseBuilding();

    float GetResourcesAmount() { return Resources; }

    void SetResources(float Amount);

    void RemoveResources(float Amount);

    void AddResources(float Amount);

protected:
    virtual void BeginPlay() override;

    void SetResourcesText(const FText& Text);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* BuildingMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* ResourcesAmountText;

    UPROPERTY(BlueprintReadOnly, Category = "Resources")
    float Resources = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resources", meta = (ClampMin = "0.0", ClampMax = "1000000.0"))
    float MaxResources = 100.0f;
};
