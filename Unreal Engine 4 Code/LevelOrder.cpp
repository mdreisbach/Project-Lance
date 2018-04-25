#include "LevelOrder.h"


// Sets default values for this component's properties
ULevelOrder::ULevelOrder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// Turn off as the Priority Algorithm only should run once.
	PrimaryComponentTick.bCanEverTick = flase;

}


// Called when the game starts
// This function serves as the driver for the Priority Algorithm
void ULevelOrder::BeginPlay()
{
	Super::BeginPlay();

	//Create three sample LevelInfo classes
	LevelInfo level0(0);
	LevelInfo level1(1);
	LevelInfo level2(2);


	//Add levels to levelList
	levelList.Add(level0);
	levelList.Add(level1);
	levelList.Add(level2);


	//Choose first 10 levels
	for (int32 i = 0; i < 10; i++) {

		LevelInfo levelPicked = selectRandomLevel();

		UE_LOG(LogTemp, Warning, TEXT("Level Selected (Pick #%d): %d"), (i + 1), levelPicked.getLevelIndex());

		levelIndexOrder.Add(levelPicked.getLevelIndex());

	}

	//Add harder levels
	LevelInfo level3(3);
	levelList.Add(level3);
	LevelInfo level4(4);
	levelList.Add(level4);
	LevelInfo level5(5);
	levelList.Add(level5);
	LevelInfo level6(6);
	levelList.Add(level6);
	LevelInfo level7(7);
	levelList.Add(level7);

	//Choose next 90 levels
	for (int32 i = 0; i < 90; i++) {

		LevelInfo levelPicked = selectRandomLevel();

		UE_LOG(LogTemp, Warning, TEXT("Level Selected (Pick #%d): %d"), (i + 1), levelPicked.getLevelIndex());

		levelIndexOrder.Add(levelPicked.getLevelIndex());

	}

	//Print the levels picked in the order
	FString levelOrder = "Order of levels: ";

	for (int32 i = 0; i < levelIndexOrder.Num(); i++) {

		levelOrder = levelOrder + FString::FromInt(levelIndexOrder[i]) + ", ";

	}

	//Print final integer array to log. This shows the order of levels to load by levelIndex
	UE_LOG(LogTemp, Warning, TEXT("%s"), *levelOrder);

}


// Called every frame
// Set to false in constructor, never runs
void ULevelOrder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

//Function selects a random LevelInfo object from the full list of levels.
LevelInfo ULevelOrder::selectRandomLevel()
{
	//Call function to generate list of levels based on priority
	generateSelectionList();

	//Random number from 0 to end of selection list index
	int32 randomIndex = FMath::RandRange(0, (selectionList.Num() - 1));

	//Turn the selection list into a String for debugging assistance
	FString selListStr = selectionListToString();

	//Print the current selection list to the log
	UE_LOG(LogTemp, Warning, TEXT("Selection List: %s"), *selListStr);

	//Turn the level list into a String for debugging assistance
	FString levelListStr = levelListToString();

	//Print the current level list to the log
	UE_LOG(LogTemp, Warning, TEXT("Level List: %s"), *levelListStr);

	//Increment the priority of the LevelInfo object choosen by the function
	levelList[selectionList[randomIndex].getLevelIndex()].incrPriority();

	//Return the selected LevelInfo object corresponding to the random index selected
	return selectionList[randomIndex];
}

//Function generates a list of LevelInfo objects with priority factored in
//A priority of 1 will have the highest chance to be selected
void ULevelOrder::generateSelectionList()
{

	selectionList.Empty();

	//Decrement priorities if none are equal to 1
	//Prevents priorities from scaling to extreme numbers
	validatePriorities();

	//Find the highest priority of any Levelinfo object
	int32 highestPriority = findHighestPriority();

	//Loop through levelList and add to selection list a number of time based on priority
	for (int32 i = 0; i < levelList.Num(); i++) {

		//If the level has a priority equal to the highest add once
		if (levelList[i].getPriority() == highestPriority) {

			selectionList.Add(levelList[i]);

		}//If the level has a priority of 1 then add as many times as the highest priority
		else if (levelList[i].getPriority() == 1) {

			for (int32 j = 0; j < highestPriority; j++) {

				selectionList.Add(levelList[i]);

			}

		}//If the level has a priority in the middle calculate dynamic number of times to add
		else {

			int numTimesToAdd = highestPriority / (levelList[i].getPriority());

			for (int32 j = 0; j < numTimesToAdd; j++) {

				selectionList.Add(levelList[i]);

			}

		}

	}

}

//Function determines the highest priority of all LevelInfo objects in levelList
//Return integer of highest priority
int32 ULevelOrder::findHighestPriority()
{

	int32 highestPriority = 1;

	for (int32 i = 0; i < levelList.Num(); i++) {

		if (levelList[i].getPriority() > highestPriority) {

			highestPriority = levelList[i].getPriority();

		}

	}

	return highestPriority;
}

//Function checks if a priority of 1 exists in LevelList
//If it does not decrement all priorities until one does
//Prevents priorities from scaling extremely high
void ULevelOrder::validatePriorities()
{

	bool hasPrioOfOne = false;

	for (int32 i = 0; i < levelList.Num(); i++) {

		if (levelList[i].getPriority() == 1) {
			hasPrioOfOne = true;
		}

	}

	if (!hasPrioOfOne) {

		for (int32 i = 0; i < levelList.Num(); i++) {

			UE_LOG(LogTemp, Warning, TEXT("calling decrPriority() on level list"));
			levelList[i].decrPriority();

		}

	}

}

//Returns the selectionList as a String displaying each objects LevelIndex and Priority
FString ULevelOrder::selectionListToString()
{

	FString listString = "";

	for (int32 i = 0; i < selectionList.Num(); i++) {

		listString = listString + "{" + FString::FromInt(selectionList[i].getLevelIndex()) + " : " + FString::FromInt(selectionList[i].getPriority()) + "}";

	}

	return listString;
}

//Returns the levelList as a String displaying each objects LevelIndex and Priority
FString ULevelOrder::levelListToString()
{

	FString listString = "";

	for (int32 i = 0; i < levelList.Num(); i++) {

		listString = listString + "{" + FString::FromInt(levelList[i].getLevelIndex()) + " : " + FString::FromInt(levelList[i].getPriority()) + "}";

	}

	return listString;
}
