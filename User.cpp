#include "User.h"

void User::set_user(string userName)
{
	name = userName;
}

string User::get_user()
{
	return name;
}

void User::set_startTime(string startT)
{
	startTime = startT;
}

string User::get_startTime()
{
	return startTime;
}

void User::set_endTime(string endT)
{
	endTime = endT;
}

string User::get_endTime()
{
	return endTime;
}

User* User::instance()
{
	if (!user)
		user = new User;
	return user;
}