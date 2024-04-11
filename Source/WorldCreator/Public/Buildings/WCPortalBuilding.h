// The project was made for a technical assignment

#pragma once

#include "CoreMinimal.h"
#include "Buildings/WCTransmitterBuilding.h"
#include "WCPortalBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTotalResourcesChanged, float, NewTotalResources);

static float TotalResources = 0;

static FOnTotalResourcesChanged OnTotalResourcesChanged;

UCLASS()
class WORLDCREATOR_API AWCPortalBuilding : public AWCTransmitterBuilding
{
    GENERATED_BODY()

public:
    virtual void AddResources(float Amount) override;

    float GetTotalResources() const { return TotalResources; }

protected:
    virtual void BeginPlay() override;

    void SetTotalResources(float NewTotalResources);
};
