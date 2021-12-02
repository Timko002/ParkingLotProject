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
int LotH::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int reservedSpot = -1;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpaceH.size(); i++)
	{
		if (pSpaceH[i]->reserve(start_hour, start_min, blocks))
		{
			reservedSpot = i + 1;
			break;
		}
	}
	return reservedSpot;
}

int LotH::getAvaialbleSlots(time_t startTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int max_available_blocks, available_blocks;

	max_available_blocks = pSpaceH[0]->getAvaialbleSlots(start_hour, start_min);

	for (int i = 1; i < pSpaceH.size(); i++)
	{
		available_blocks = pSpaceH[i]->getAvaialbleSlots(start_hour, start_min);
		if (available_blocks > max_available_blocks)
			max_available_blocks = available_blocks;

	}
	return max_available_blocks;
}

int LotH::getNoOfTotallyBookedSpots()
{
	int NoOfTotallyBookedSpots = 0;
	for (int i = 0; i < pSpaceH.size(); i++)
	{
		if (pSpaceH[i]->checkIsFull()) //if even one space is free, it is not full
		{
			NoOfTotallyBookedSpots++;
		}
	}
	return NoOfTotallyBookedSpots;
}
string LotH::getFirstAvailableSlot(int currHour, int currMin)
{
	int starting_index;
	int starting_hour_index = (currHour * 4) - 36;

	switch (currMin)
	{
	case 15:
		starting_index = starting_hour_index + 1;
		break;
	case 30:
		starting_index = starting_hour_index + 2;
		break;
	case 45:
		starting_index = starting_hour_index + 3;
		break;
	default:
		starting_index = starting_hour_index;
	}
	int available_block, first_available_block;

	first_available_block = 1000;

	for (int i = 0; i < pSpaceH.size(); i++)
	{
		available_block = pSpaceH[i]->getFirstAvailableSlot(starting_index);
		if (available_block == -1)
			continue;
		if (available_block == starting_index)
		{
			first_available_block = starting_index;
			break;
		}
		if (available_block < first_available_block)
			first_available_block = available_block;
	}
	int rem = first_available_block % 4;
	string min, hour;
	switch (rem)
	{
	case 1:
		min = "15";
		break;
	case 2:
		min = "30";
		break;
	case 3:
		min = "45";
		break;
	default:
		min = "00";
	}
	int q = first_available_block - rem;
	int hr = (q + 36) / 4;
	hour = to_string(hr);
	return (hour + ":" + min);

}
// !LotH