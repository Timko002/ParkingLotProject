#pragma once
#ifndef DBOBJECT_H
#define DBOBJECT_H
#include <iostream>
#include <mysql.h>
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
	public:
		DBObject()
		{
			Driver = get_driver_instance();  // Driver to connect the database
			Con = Driver->connect("tcp://127.0.0.1:3306", "root", "password");   // Connecting the database using driver's connection method

			Cstm = Con->createStatement();  //Access the database

			Cstm->execute("use parking"); //using parking database
		}
		string checkLogin(string userName, string pass);
		bool checkUserExists(string userName);
		void createUser(string userName, string pass);
		void bookUser(string userName, string lot, string space_no, string startTime, string endTime);
	protected:
		sql::Driver* Driver;
		sql::Connection* Con;
		sql::ResultSet* res;
		sql::Statement* Cstm;
		string command;
};

#endif // !DBOBJECT_H