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
int LotG::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int reservedSpot = -1;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceG.size(); i++)
	{
		if (pSpaceG[i]->reserve(start_hour, start_min, blocks))
		{
			reservedSpot = i + 1;
			break;
		}
	}
	return reservedSpot;
}

int LotG::getAvaialbleSlots(time_t startTime)
{
	tm* st = gmtime(&startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int max_available_blocks, available_blocks;

	max_available_blocks = pSpaceG[0]->getAvaialbleSlots(start_hour, start_min);

	for (int i = 1; i < pSpaceG.size(); i++)
	{
		available_blocks = pSpaceG[i]->getAvaialbleSlots(start_hour, start_min);
		if (available_blocks > max_available_blocks)
			max_available_blocks = available_blocks;

	}
	return max_available_blocks;
}

int LotG::getNoOfTotallyBookedSpots()
{
	int NoOfTotallyBookedSpots = 0;
	for (int i = 0; i < pSpaceG.size(); i++)
	{
		if (pSpaceG[i]->checkIsFull()) //if even one space is free, it is not full
		{
			NoOfTotallyBookedSpots++;
		}
	}
	return NoOfTotallyBookedSpots;
}
// !LotG