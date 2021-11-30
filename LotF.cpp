#pragma once
#include "LotF.h"
LotF* LotF::f_instance = 0;
string LotF::getLotName()
{
	return LotName;
}
int LotF::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotF::checkIsLotFull()
{
	for (int i = 0; i < pSpaceF.size(); i++)
	{
		if (!pSpaceF[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotF* LotF::getInstance()
{
	if (!f_instance)
		f_instance = new LotF();
	return f_instance;
}
bool LotF::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceF.size(); i++)
	{
		if (pSpaceF[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}
int LotF::getAvaialbleSlots(time_t startTime)
{
	tm* st = gmtime(&startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int max_available_blocks, available_blocks;

	max_available_blocks = pSpaceF[0]->getAvaialbleSlots(start_hour, start_min);

	for (int i = 1; i < pSpaceF.size(); i++)
	{
		available_blocks = pSpaceF[i]->getAvaialbleSlots(start_hour, start_min);
		if (available_blocks > max_available_blocks)
			max_available_blocks = available_blocks;

	}
	return max_available_blocks;
}
// !LotF