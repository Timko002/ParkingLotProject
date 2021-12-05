#pragma once
#ifndef LotF_H
#define LotF_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotF
class LotF : public Lot
{
	const string LotName = "F";
	const int TotalNoOfSpots = 100;
	static LotF* f_instance;

	LotF()
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

	static LotF* getInstance();

};

#endif