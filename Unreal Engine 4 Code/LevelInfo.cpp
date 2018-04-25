#include "LevelInfo.h"

LevelInfo::LevelInfo(int32 index)
{
	priority = 1;
	levelIndex = index;
}


LevelInfo::~LevelInfo()
{
}

int32 LevelInfo::getPriority()
{
	return priority;
}

void LevelInfo::setPriority(int32 number)
{
	priority = number;
}

int32 LevelInfo::getLevelIndex()
{
	return levelIndex;
}

void LevelInfo::setLevelIndex(int32 index)
{
	levelIndex = index;
}

void LevelInfo::incrPriority()
{
	priority++;
}

void LevelInfo::decrPriority()
{
	priority--;
}