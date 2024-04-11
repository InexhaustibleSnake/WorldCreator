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

    UFUNCTION(BlueprintCallable, Category = "Buildings")
    void SetResources(float Amount);
    float GetResourcesAmount() { return Resources; }

    float GetMaxResourcesAmount() { return MaxResources; }

    void RemoveResources(float Amount);

    void AddResources(float Amount);

    void SetIsLoaded(bool Loaded) { IsLoaded = Loaded; }
    bool GetIsLoaded() const { return IsLoaded; }

protected:
    virtual void BeginPlay() override;

    void SetResourcesText(const FText& Text);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* BuildingMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* ResourcesAmountText;

    UPROPERTY()
    float Resources = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resources", meta = (ClampMin = "0.0", ClampMax = "1000000.0"))
    float MaxResources = 100.0f;

    UPROPERTY()
    bool IsLoaded = true;
};
