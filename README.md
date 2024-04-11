# WorldCreator 

This is a simple project created on UE 4.27

User can build buildings and "switch levels"


Control:

Mouse - Spin the camera

WASD - Walk

Q - Previous level

E - Next level

1 - Build Source Building 

2 - Build Transmitter Building

3 - Build Portal Building

Changing worlds:

The user can "change worlds". Each world is initially empty and is a flat surface. Created buildings in a world are saved and updated even if another world is loaded

![image](https://github.com/InexhaustibleSnake/WorldCreator/assets/93211950/248ce3d6-e593-4e84-8dad-c1e5c7672b47)

The WCLevelManagerComponent is responsible for changing the world. It contains a variable CurrentLevelIndex, which becomes larger or smaller when the world is changed. 
When the world is changed, the buildings created in this world are added to the LevelsData array, after which they are "unloading" (their visibility and collision are disabled)

When loading a new world, CurrentLevelIndex is passed to the LevelsData array, which gives us an array of buildings to enable visibility and collision

![image](https://github.com/InexhaustibleSnake/WorldCreator/assets/93211950/727bd1ef-9371-43a0-99ab-487fa3ec5803)

The reason the LevelsData array contains a structure and not an array of buildings is because nested containers are not supported

![image](https://github.com/InexhaustibleSnake/WorldCreator/assets/93211950/5cfd4e4b-de77-445b-8544-7c467f4b7ad1)


Buildings:

There are four types of buildings: 
1) BaseBuilding - the base class for all buildings
   
2) SourceBuilding - a regular building. Has the maximum amount of resources when spawning

3) TransmitterBuilding - takes resources from the nearest building at a speed of 1 second in the amount of 1
 
![image](https://github.com/InexhaustibleSnake/WorldCreator/assets/93211950/4cd58c50-b928-4b99-8406-b70a96aa4a45)

On BeginPlay, this building simply looks for the nearest loaded building and takes resources from it 

![image](https://github.com/InexhaustibleSnake/WorldCreator/assets/93211950/1942eb10-6ee8-4d17-83be-6c1f48210a67)

If the target building is found, the arrow points in its direction

4) PortalBuilding - a child class of TransmitterBuilding. Unlike TransmitterBuilding, buildings of this type have the TotalResources parameter. This parameter is the same for all buildings of this type in all worlds and is updated instead of the Resources parameter.

![image](https://github.com/InexhaustibleSnake/WorldCreator/assets/93211950/c6d11816-f033-4383-844f-0e26e68f5574)

The PortalBuilding class has a static TotalResources variable that is updated instead of Resources. It also has a static delegate

![image](https://github.com/InexhaustibleSnake/WorldCreator/assets/93211950/fedc91f9-96f0-4ee3-acfe-6341da26edc4)

Also overrides functions related to adding resources (just replaces Resources with TotalResources)

