#pragma once

#include "LotE.h"
LotE* LotE::e_instance = 0;
string LotE::getLotName()
{
	return LotName;
}
int LotE::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotE::checkIsLotFull()
{
	for (int i = 0; i < pSpaceE.size(); i++)
	{
		if (!pSpaceE[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotE* LotE::getInstance()
{
	if (!e_instance)
		e_instance = new LotE();
	return e_instance;
}
bool LotE::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceE.size(); i++)
	{
		if (pSpaceE[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}
 // !LotE