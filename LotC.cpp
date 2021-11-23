#include "LotC.h"
LotC* LotC::c_instance = 0;
string LotC::getLotName()
{
	return LotName;
}
int LotC::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
bool LotC::checkIsLotFull()
{
	for (int i = 0; i < pSpaceC.size(); i++)
	{
		if (!pSpaceC[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}
 LotC* LotC::getInstance()
{
	if (!c_instance)
		c_instance = new LotC();
	return c_instance;
}
bool LotC::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	gmtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceC.size(); i++)
	{
		if (pSpaceC[i]->reserve(start_hour, start_min, blocks))
		{
			reserve_flag = true;
			break;
		}
	}
	return reserve_flag;
}
