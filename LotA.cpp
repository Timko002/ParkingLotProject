#pragma once
#include "LotA.h"
#include <string>

LotA* LotA::a_instance = 0;
string LotA::getLotName()
{
	return LotName;
}
int LotA::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotA::checkIsLotFull()
{
	for (int i = 0; i < pSpaceA.size(); i++)
	{
		if (!pSpaceA[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotA* LotA::getInstance()
{
	if (!a_instance)
		a_instance = new LotA();
	return a_instance;
}
bool LotA::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	localtime_s(st,&startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	cout << blocks;
	for (int i = 0; i < pSpaceA.size(); i++)
	{
		if (pSpaceA[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}

int LotA::getAvaialbleSlots(time_t startTime)
{
	tm* st = gmtime(&startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int max_available_blocks, available_blocks;

	max_available_blocks = pSpaceA[0]->getAvaialbleSlots(start_hour, start_min);

	for (int i = 1; i < pSpaceA.size(); i++)
	{
		available_blocks = pSpaceA[i]->getAvaialbleSlots(start_hour, start_min);
		if (available_blocks > max_available_blocks)
			max_available_blocks = available_blocks;

	}
	return max_available_blocks;
}
 // !LOTA