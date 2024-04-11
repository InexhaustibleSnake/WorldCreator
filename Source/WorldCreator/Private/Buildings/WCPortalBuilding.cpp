// The project was made for a technical assignment

#include "Buildings/WCPortalBuilding.h"

void AWCPortalBuilding::BeginPlay()
{
    Super::BeginPlay();

    OnTotalResourcesChanged.AddDynamic(this, &AWCPortalBuilding::OnResourcesChanged);

    SetResourcesText(FText::FromString(FString::SanitizeFloat(TotalResources)));
}

void AWCPortalBuilding::AddResources(float Amount) 
{
    SetTotalResources(GetTotalResources() + Amount);
}


void AWCPortalBuilding::SetTotalResources(float NewTotalResources)
{
    TotalResources = NewTotalResources;

    OnTotalResourcesChanged.Broadcast(GetTotalResources());
}
