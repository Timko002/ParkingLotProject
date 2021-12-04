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
//returns the time left in minutes
int TimerFunctions::returnTimeLeft(string timeEnd)
{
	time_t currentTime;
	struct tm* localTime;
	string stringToAdd;

	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	int localH = localTime->tm_hour;
	int localM = localTime->tm_min;
	int timeEndHour;
	int timeEndMin;
	if (timeEnd.size() > 4)
	{
		timeEndHour = stoi(timeEnd.substr(0, 2));
		timeEndMin = stoi(timeEnd.substr(3, 2));
	}
	else
	{
		timeEndHour = stoi(timeEnd.substr(0, 1));
		timeEndMin = stoi(timeEnd.substr(2, 2));
	}
	return ((timeEndHour - localH) * 60 + (timeEndMin - localM));
}
vector<wxString> TimerFunctions::returnComboOptions(vector<wxString> vectorStringToadd, int Hours, int Minutes)
{
	string stringToAdd;
	while (Hours < 18)
	{
		for (Minutes;  Minutes < 60; Minutes += 15)
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

vector<wxString> TimerFunctions::returnComboOptionsForEndTime(vector<wxString> vectorStringToadd, int Hours, int Minutes, int count_blocks)
{
	string stringToAdd;
	int counter = 0;
	while (counter < count_blocks && Hours < 18)
	{
		for (Minutes; counter < count_blocks && Minutes < 60; Minutes += 15)
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
			counter++;
		}
		Minutes = 0;
		Hours++;
	}
	if (counter < count_blocks)
		vectorStringToadd.push_back("18:00");
	return vectorStringToadd;
}

time_t TimerFunctions::convertChoiceTime(string choice)
{

	time_t currentTime;
	struct tm* localTime;
	int localH = stoi(choice.substr(0,2));
	int localM = stoi(choice.substr(choice.length() - 2));
	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	localTime->tm_hour = localH;
	localTime->tm_min = localM;

	return mktime(localTime);
}
