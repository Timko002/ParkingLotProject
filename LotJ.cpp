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
	gmtime_s(st, &startTime);
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
// !LotJ