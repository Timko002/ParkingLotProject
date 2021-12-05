#ifndef LotC_H
#define LotC_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotC
class LotC : public Lot
{
	const string LotName = "C";
	const int TotalNoOfSpots = 100;
	static LotC* c_instance;

	LotC()
	{
		DBObject::instance()->command = "select * from " + LotName + " ORDER BY Space_No ASC";
		DBObject::instance()->res = DBObject::instance()->Cstm->executeQuery(DBObject::instance()->command);
		int i = 0;
		while (DBObject::instance()->res->next()) {
			//creates the parking space instances and initializes the values from the DB
			pSpace.push_back(new ParkingSpace(100, 100, LotName, i + 1));
			i++;
		}
	}

public:
	string getLotName();

	int getTotalNoOfSpots();

	static LotC* getInstance();

};

#endif