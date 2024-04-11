// The project was made for a technical assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WCBaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourcesAmountChanged, float, NewResources);

class UTextRenderComponent;

UCLASS()
class WORLDCREATOR_API AWCBaseBuilding : public AActor
{
    GENERATED_BODY()

public:
    AWCBaseBuilding();

    UFUNCTION(BlueprintCallable, Category = "Buildings")
    virtual void SetResources(float Amount);
    float GetResourcesAmount() { return Resources; }

    float GetMaxResourcesAmount() { return MaxResources; }

    void RemoveResources(float Amount);

    virtual void AddResources(float Amount);

    void SetIsLoaded(bool Loaded) { IsLoaded = Loaded; }
    bool GetIsLoaded() const { return IsLoaded; }

    UPROPERTY(BlueprintAssignable)
    FOnResourcesAmountChanged OnResourcesAmountChanged;

protected:
    virtual void BeginPlay() override;

    void SetResourcesText(const FText& Text);

    UFUNCTION()
    void OnResourcesChanged(float NewResources);

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
