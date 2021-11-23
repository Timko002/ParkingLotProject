#include "LotB.h"
LotB* LotB::b_instance = 0;
string LotB::getLotName()
{
	return LotName;
}
int LotB::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotB::checkIsLotFull()
{
	for (int i = 0; i < pSpaceB.size(); i++)
	{
		if (!pSpaceB[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
LotB* LotB::getInstance()
{
	if (!b_instance)
		b_instance = new LotB();
	return b_instance;
}
bool LotB::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	gmtime_s(st, &startTime);;
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceB.size(); i++)
	{
		if (pSpaceB[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}