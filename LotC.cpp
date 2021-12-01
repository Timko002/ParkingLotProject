#pragma once

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
 int LotC::reserve(time_t startTime, time_t endTime)
 {
	 tm* st = new tm();
	 localtime_s(st, &startTime);
	 int start_hour = st->tm_hour;
	 int start_min = st->tm_min;
	 int reservedSpot = -1;
	 int blocks = int(difftime(endTime, startTime) / 900);

	 for (int i = 0; i < pSpaceC.size(); i++)
	 {
		 if (pSpaceC[i]->reserve(start_hour, start_min, blocks))
		 {
			 reservedSpot = i + 1;
			 break;
		 }
	 }
	 return reservedSpot;
 }

 int LotC::getAvaialbleSlots(time_t startTime)
 {
	 tm* st = gmtime(&startTime);
	 int start_hour = st->tm_hour;
	 int start_min = st->tm_min;
	 int max_available_blocks, available_blocks;

	 max_available_blocks = pSpaceC[0]->getAvaialbleSlots(start_hour, start_min);

	 for (int i = 1; i < pSpaceC.size(); i++)
	 {
		 available_blocks = pSpaceC[i]->getAvaialbleSlots(start_hour, start_min);
		 if (available_blocks > max_available_blocks)
			 max_available_blocks = available_blocks;

	 }
	 return max_available_blocks;
 }

 int LotC::getNoOfTotallyBookedSpots()
 {
	 int NoOfTotallyBookedSpots = 0;
	 for (int i = 0; i < pSpaceC.size(); i++)
	 {
		 if (pSpaceC[i]->checkIsFull()) //if even one space is free, it is not full
		 {
			 NoOfTotallyBookedSpots++;
		 }
	 }
	 return NoOfTotallyBookedSpots;
 }
 // !LotC