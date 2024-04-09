// The project was made for a technical assignment

#include "WCGameMode.h"
#include "Player/WCPlayerCharacter.h"

AWCGameMode::AWCGameMode() 
{
    DefaultPawnClass = AWCPlayerCharacter::StaticClass();
}
