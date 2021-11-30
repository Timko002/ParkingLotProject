#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
	static User* user;
	User()
	{
		userStatus = "unreserved";
	}
	public:
		void set_user(string userName);
		string get_user();
		void set_startTime(string startT);
		string get_startTime();
		void set_status(string status);
		string get_status();
		void set_endTime(string endT);
		string get_endTime();
		void setReservedLot(string lot);
		void setReservedSpot(string spot);
		string getReservedLot();
		string getReservedSpot();
		static User* instance();
	protected:
		string name;
		string userStatus;
		string reservedLot;
		string reservedSpot;
		string startTime;
		string endTime;
};
#endif // !USER_H
