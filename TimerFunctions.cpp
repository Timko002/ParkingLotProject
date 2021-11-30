#pragma once
#include "TimerFunctions.h"
void TimerFunctions::setCurrentTime()
{
	time_t currentTime;
	struct tm* localTime;
	string stringToAdd;

	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	int localH = localTime->tm_hour;
	if (localH < 6)
	{
		localH = 6;
	}

	int localM = localTime->tm_min;
	// Directing Min to next 15 min block
	if (localM == 0)
	{
		// do nothing
	}
	else if (localM <= 15)
	{
		localM = 15;
	}
	else if (localM <= 30)
	{
		localM = 30;
	}
	else if (localM <= 45)
	{
		localM = 45;
	}
	else
	{
		localM = 0;
		localH += 1;
	}
	Hour = localH;
	Min = localM;
}
int TimerFunctions::returnHour()
{
	return Hour;
}
int TimerFunctions::returnMin()
{
	return Min;
}
int TimerFunctions::returnTimeLeft()
{
	return 0;
}
vector<wxString> TimerFunctions::returnComboOptions(vector<wxString> vectorStringToadd, int Hours, int Minutes)
{
	string stringToAdd;
	while (Hours < 18)
	{
		for (Minutes; Minutes < 60; Minutes += 15)
		{
			stringToAdd = to_string(Hours);
			stringToAdd += ":";
			if (Minutes == 0)
			{
				stringToAdd += "00";
			}
			else
			{
				stringToAdd += to_string(Minutes);
			}
			vectorStringToadd.push_back(stringToAdd);
		}
		Minutes = 0;
		Hours++;
	}
	return vectorStringToadd;
}

time_t TimerFunctions::convertChoiceTime(string choice)
{

	time_t currentTime;
	struct tm* localTime;
	int localH = stoi(choice.substr(0,2));
	int localM = stoi(choice.substr(3,4));
	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	localTime->tm_hour = localH;
	localTime->tm_min = localM;

	return mktime(localTime);
}
