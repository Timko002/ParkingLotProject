#pragma once
#include "LotH.h"
LotH* LotH::h_instance = 0;
string LotH::getLotName()
{
	return LotName;
}
int LotH::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotH::checkIsLotFull()
{
	for (int i = 0; i < pSpaceH.size(); i++)
	{
		if (!pSpaceH[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotH* LotH::getInstance()
{
	if (!h_instance)
		h_instance = new LotH();
	return h_instance;
}
bool LotH::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	gmtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceH.size(); i++)
	{
		if (pSpaceH[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}
// !LotH