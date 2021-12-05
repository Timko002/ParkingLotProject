#pragma once
#ifndef LotI_H
#define LotI_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotI
class LotI : public Lot
{
	const string LotName = "I";
	const int TotalNoOfSpots = 100;
	static LotI* i_instance;

	LotI()
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

	static LotI* getInstance();

};

#endif