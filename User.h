#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
	static User* user;
	User()
	{
	}
	public:
		void set_user(string userName);
		string get_user();
		void set_startTime(string startT);
		string get_startTime();
		void set_endTime(string endT);
		string get_endTime();
		static User* instance();
	protected:
		string name;
		bool isReserved;
		string startTime;
		string endTime;
};
#endif // !USER_H
