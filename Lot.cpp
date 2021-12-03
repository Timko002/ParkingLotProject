#pragma once

#include "Lot.h"
#include <string>

bool Lot::checkIsLotFull()
{
	for (int i = 0; i < pSpace.size(); i++)
	{
		if (!pSpace[i]->checkIsFull()) //if even one space is free, it is not full
		{
			isLotFull = false;
			return isLotFull;
		}
	}
	isLotFull = true;
	return isLotFull;
}

int Lot::reserve(time_t startTime, time_t endTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int reservedSpot = -1;
	int blocks = int(difftime(endTime, startTime) / 900);

	for (int i = 0; i < pSpace.size(); i++)
	{
		if (pSpace[i]->reserve(start_hour, start_min, blocks))
		{
			reservedSpot = i + 1;
			break;
		}
	}
	return reservedSpot;
}

int Lot::getAvaialbleSlots(time_t startTime)
{
	tm* st = new tm();
	localtime_s(st, &startTime);
	int start_hour = st->tm_hour;
	int start_min = st->tm_min;
	int max_available_blocks, available_blocks;

	max_available_blocks = pSpace[0]->getAvaialbleSlots(start_hour, start_min);

	for (int i = 1; i < pSpace.size(); i++)
	{
		available_blocks = pSpace[i]->getAvaialbleSlots(start_hour, start_min);
		if (available_blocks > max_available_blocks)
			max_available_blocks = available_blocks;

	}
	return max_available_blocks;
}

int Lot::getNoOfTotallyBookedSpots()
{
	int NoOfTotallyBookedSpots = 0;
	for (int i = 0; i < pSpace.size(); i++)
	{
		if (pSpace[i]->checkIsFull()) //if even one space is free, it is not full
		{
			NoOfTotallyBookedSpots++;
		}
	}
	return NoOfTotallyBookedSpots;
}
vector<wxString> Lot::getAvailableSlotsToStart(int currHour, int currMin)
{
	vector<int> availabletTimeSlots;
	vector<int> temp_availabletTimeSlots;
	vector<int>::iterator ip;
	int starting_index;
	string min, hour;
	vector<wxString> startTimeCombo;
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
	
	for (int i = 0; i < pSpace.size(); i++)
	{
		temp_availabletTimeSlots = pSpace[i]->getAvailableSlotsToStart(starting_index);
		availabletTimeSlots.insert(availabletTimeSlots.end(), temp_availabletTimeSlots.begin(), temp_availabletTimeSlots.end());
	}
	sort(availabletTimeSlots.begin(), availabletTimeSlots.end());
	ip= unique(availabletTimeSlots.begin(), availabletTimeSlots.end());
	availabletTimeSlots.resize(distance(availabletTimeSlots.begin(), ip));

	for (int i = 0; i < availabletTimeSlots.size(); i++)
	{
		int rem = availabletTimeSlots.at(i) % 4;

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
		int q = availabletTimeSlots.at(i) - rem;
		int hr = (q + 36) / 4;
		hour = to_string(hr);
		startTimeCombo.push_back(wxString(hour + ":" + min));
	}
	return startTimeCombo;
}
// !Lot