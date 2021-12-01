#include "ParkingSpace.h"
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
using namespace std;
bool ParkingSpace::checkIsFull()
{
	// If any one timeSlot is true, i.e. free return false
	// Else return true
	string s5[] = { "T9_00","T9_15","T9_30","T9_45","T10_00","T10_15","T10_30","T10_45","T11_00","T11_15","T11_30","T11_45","T12_00","T12_15","T12_30","T12_45","T13_00","T13_15","T13_30","T13_45","T14_00","T14_15","T14_30","T14_45","T15_00","T15_15","T15_30","T15_45","T16_00","T16_15","T16_30","T16_45","T17_00","T17_15","T17_30","T17_45","T18_00" };

	for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
	{
		DBObject::instance()->command = "select " + s5[i] + " from" + LotName + "where Space_No = " + to_string(SpaceNo);
		DBObject::instance()->res = DBObject::instance()->Cstm->executeQuery(DBObject::instance()->command);
		while (DBObject::instance()->res->next()) {

			timeSlot[i] = DBObject::instance()->res->getBoolean(s5[i]);

		}
		
	}
	for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
	{
		if (timeSlot[i] == true)
			return false;
	}
	return true;

}

/*9:00 = 0
  9:15 = 1
  9:30 = 2
  ...
  6:00 = 36
*/
bool ParkingSpace::reserve(int start_hour, int start_min, int blocks)
{
	string s5[] = { "T9_00","T9_15","T9_30","T9_45","T10_00","T10_15","T10_30","T10_45","T11_00","T11_15","T11_30","T11_45","T12_00","T12_15","T12_30","T12_45","T13_00","T13_15","T13_30","T13_45","T14_00","T14_15","T14_30","T14_45","T15_00","T15_15","T15_30","T15_45","T16_00","T16_15","T16_30","T16_45","T17_00","T17_15","T17_30","T17_45","T18_00" };

	for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
	{
		DBObject::instance()->command = "select " + s5[i] + " from" + LotName + "where Space_No = " + to_string(SpaceNo);
		DBObject::instance()->res = DBObject::instance()->Cstm->executeQuery(DBObject::instance()->command);
		while (DBObject::instance()->res->next()) {

			timeSlot[i] = DBObject::instance()->res->getBoolean(s5[i]);

		}

	}
	int starting_index;
	int starting_hour_index = (start_hour * 4) - 36;
	bool flag = true;
	switch (start_min)
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

	for (int i = starting_index; i <= starting_index + blocks; i++)
	{
		if (timeSlot[i] == false)
		{
			flag = false;
			break;
		}
	}
	if (flag == true)
	{
		for (int i = starting_index; i <= starting_index + blocks; i++)
		{
			timeSlot[i] = false;
			DBObject::instance()->command = "update " + LotName + " set " + s5[i] + " = False where Space_No = " + to_string(SpaceNo);
			int a = DBObject::instance()->Cstm->executeUpdate(DBObject::instance()->command);
		}
	}
	return flag;
}
int ParkingSpace::getAvaialbleSlots(int start_hour, int start_min)
{
	string s5[] = { "T9_00","T9_15","T9_30","T9_45","T10_00","T10_15","T10_30","T10_45","T11_00","T11_15","T11_30","T11_45","T12_00","T12_15","T12_30","T12_45","T13_00","T13_15","T13_30","T13_45","T14_00","T14_15","T14_30","T14_45","T15_00","T15_15","T15_30","T15_45","T16_00","T16_15","T16_30","T16_45","T17_00","T17_15","T17_30","T17_45","T18_00" };

	for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
	{
		DBObject::instance()->command = "select " + s5[i] + " from" + LotName + "where Space_No = " + to_string(SpaceNo);
		DBObject::instance()->res = DBObject::instance()->Cstm->executeQuery(DBObject::instance()->command);
		while (DBObject::instance()->res->next()) {

			timeSlot[i] = DBObject::instance()->res->getBoolean(s5[i]);

		}

	}
	int starting_index;
	int starting_hour_index = (start_hour * 4) - 36;
	
	switch (start_min)
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
	int count_blocks = 0;
	for (int i = starting_index; i < AVAILABILITY_OF_TIME_SLOT; i++)
	{
		if (timeSlot[i] == false)
			break;
		count_blocks++;
	}
	return count_blocks;
}