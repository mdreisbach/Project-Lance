#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <random>
#include "LevelInfo.h"
#include "LevelOrder.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNNERTEST_API ULevelOrder : public UActorComponent
{
	GENERATED_BODY()

public:
	ULevelOrder();	// Sets default values for this component's properties
	LevelInfo selectRandomLevel();	// Function returns a random LevelInfo object
	//Integer array to be return from algorithm holder level indexes
	//Using a UPROPERTY to allow the array to be visible to Blueprint script and prevent garbage collection
	//TArray is Unreal Engines version of a dynamically sized array
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = levelIndexOrder) TArray <int32> levelIndexOrder;

protected:
	// Called when the game starts, serves as driver for the priority algorithm
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray <LevelInfo> levelList;		//Holds the current levels factored into the algorithm
	TArray <LevelInfo> selectionList;	//Array of the current levels to be picked from, levels with a higher priority have multiple indexes
	void generateSelectionList();		//Generates list of levels with priority factored in
	int32 findHighestPriority();		//Find the highest priority in the levelList
	void validatePriorities();			//Determine is a priority of 1 exists, decrement until it does
	FString selectionListToString();	//To String for selectionList, FString is Unreal's String datatype
	FString levelListToString();		//To String for levelList
	
};
