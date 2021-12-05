#pragma once
#ifndef LotE_H
#define LotE_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotE
class LotE : public Lot
{
	const string LotName = "E";
	const int TotalNoOfSpots = 100;
	static LotE* e_instance;

	LotE()
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

	static LotE* getInstance();

};

#endif