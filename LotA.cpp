#include "LotA.h"
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
	gmtime_s(st,&startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	bool reserve_flag = false;
	int blocks = int(difftime(endTime, startTime) / 900);

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