#pragma once
#ifndef DBOBJECT_H
#define DBOBJECT_H
#include <iostream>
#include <mysql.h>
#include <wx/wx.h>
#include <jdbc\cppconn\connection.h>
#include <jdbc\cppconn\exception.h>
#include <jdbc\cppconn\resultset.h>
#include <jdbc\cppconn\statement.h>
#include <jdbc\mysql_connection.h>
#include <jdbc\mysql_driver.h>

using namespace std;
using namespace sql;

class DBObject
{
		static DBObject* db;
		DBObject()
		{
			Driver = get_driver_instance();  // Driver to connect the database
			Con = Driver->connect("tcp://127.0.0.1:3306", "root", "password");   // Connecting the database using driver's connection method

			Cstm = Con->createStatement();  //Access the database

			Cstm->execute("use parking"); //using parking database
		}
	public:
		// checks login credentials in DB
		string checkLogin(string userName, string pass);
		// checks if a user exists
		bool checkUserExists(string userName);
		// creates a new user
		void createUser(string userName, string pass);
		// books a user in a specific lot and space number
		void bookUser(string userName, string lot, string space_no, string startTime, string endTime);
		// checks if you are reserved already
		bool isReserved(string userName);
		// updates the previously parked users rating
		void updateRating(int rating);
		// gets user info
		void getUserInfo(string userName);
		// checks if you should open rating panel
		bool checkToRate(string lot, string space_no, string startTime);
		// updates your user status
		void updateStatus(string status, string username);
		static DBObject* instance();
	//protected:
		sql::Driver* Driver;
		sql::Connection* Con;
		sql::ResultSet* res;
		sql::Statement* Cstm;
		string command;
};

#endif // !DBOBJECT_H