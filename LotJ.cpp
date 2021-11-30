#pragma once
#include "LotJ.h"
LotJ* LotJ::j_instance = 0;
string LotJ::getLotName()
{
	return LotName;
}
int LotJ::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotJ::checkIsLotFull()
{
	for (int i = 0; i < pSpaceJ.size(); i++)
	{
		if (!pSpaceJ[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotJ* LotJ::getInstance()
{
	if (!j_instance)
		j_instance = new LotJ();
	return j_instance;
}
bool LotJ::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceJ.size(); i++)
	{
		if (pSpaceJ[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}
int LotJ::getAvaialbleSlots(time_t startTime)
{
	tm* st = gmtime(&startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int max_available_blocks, available_blocks;

	max_available_blocks = pSpaceJ[0]->getAvaialbleSlots(start_hour, start_min);

	for (int i = 1; i < pSpaceJ.size(); i++)
	{
		available_blocks = pSpaceJ[i]->getAvaialbleSlots(start_hour, start_min);
		if (available_blocks > max_available_blocks)
			max_available_blocks = available_blocks;

	}
	return max_available_blocks;
}
// !LotJ