#pragma once
#include "LotG.h"
LotG* LotG::g_instance = 0;
string LotG::getLotName()
{
	return LotName;
}
int LotG::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotG::checkIsLotFull()
{
	for (int i = 0; i < pSpaceG.size(); i++)
	{
		if (!pSpaceG[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotG* LotG::getInstance()
{
	if (!g_instance)
		g_instance = new LotG();
	return g_instance;
}
bool LotG::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	gmtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceG.size(); i++)
	{
		if (pSpaceG[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}
// !LotG