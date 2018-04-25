#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RUNNERTEST_API LevelInfo
{
private:
	int32 priority;		//Integer for level's priority, int32 is Unreal's version of signed integer data type
	int32 levelIndex;	//Integer for level's index. Corresponds to array of levels in RunGameMode Blueprint Script
public:
	LevelInfo(int32 index);
	~LevelInfo();
	int32 getPriority();
	void setPriority(int32 number);
	int32 getLevelIndex();
	void setLevelIndex(int32 index);
	void incrPriority();
	void decrPriority();
};
