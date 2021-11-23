#pragma once
#ifndef LOTD
#define LOTD
#include "LotD.h"
LotD* LotD::d_instance = 0;
string LotD::getLotName()
{
	return LotName;
}
int LotD::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotD::checkIsLotFull()
{
	for (int i = 0; i < pSpaceD.size(); i++)
	{
		if (!pSpaceD[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotD* LotD::getInstance()
{
	if (!d_instance)
		d_instance = new LotD();
	return d_instance;
}
bool LotD::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	gmtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceD.size(); i++)
	{
		if (pSpaceD[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}
#endif //  !LOTD