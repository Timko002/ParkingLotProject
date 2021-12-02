#pragma once
#ifndef ParkingSpace_H
#define ParkingSpace_H
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <mysql.h>
#include <jdbc\cppconn\connection.h>
#include <jdbc\cppconn\exception.h>
#include <jdbc\cppconn\resultset.h>
#include <jdbc\cppconn\statement.h>
#include <jdbc\mysql_connection.h>
#include <jdbc\mysql_driver.h>
#include "DBObject.h"
#define AVAILABILITY_OF_TIME_SLOT 36
using namespace std;
class ParkingSpace
{

	int dim_x;
	int dim_y;
	bool isFull;
	bool timeSlot[AVAILABILITY_OF_TIME_SLOT+1];
	string LotName;
	int SpaceNo;
	public:
		ParkingSpace(int x, int y, string Lot, int Space)
		{
			dim_x = x;
			dim_y = y;
			LotName = Lot;
			SpaceNo = Space;
			//for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
			//	timeSlot[i] = true;
			string s5[] = { "T9_00","T9_15","T9_30","T9_45","T10_00","T10_15","T10_30","T10_45","T11_00","T11_15","T11_30","T11_45","T12_00","T12_15","T12_30","T12_45","T13_00","T13_15","T13_30","T13_45","T14_00","T14_15","T14_30","T14_45","T15_00","T15_15","T15_30","T15_45","T16_00","T16_15","T16_30","T16_45","T17_00","T17_15","T17_30","T17_45","T18_00" };
			DBObject::instance()->command = "select * from " + LotName + " where Space_No = " + to_string(SpaceNo);
			DBObject::instance()->res = DBObject::instance()->Cstm->executeQuery(DBObject::instance()->command);

			while (DBObject::instance()->res->next()) {
				for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
				{
					timeSlot[i] = DBObject::instance()->res->getBoolean(s5[i]);
				}

			}
			
		}

		bool checkIsFull();
		
		bool reserve(int start_hour, int start_min, int blocks);

		int getAvaialbleSlots(int start_hour, int start_min);

		int getFirstAvailableSlot(int starting_index);
		
};
#endif