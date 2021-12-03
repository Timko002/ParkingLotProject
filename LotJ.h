#pragma once
#ifndef LotJ_H
#define LotJ_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotJ
class LotJ : public Lot
{
	const string LotName = "J";
	const int TotalNoOfSpots = 100;
	static LotJ* j_instance;

	LotJ()
	{
		DBObject::instance()->command = "select * from " + LotName + " ORDER BY Space_No ASC";
		DBObject::instance()->res = DBObject::instance()->Cstm->executeQuery(DBObject::instance()->command);
		int i = 0;
		while (DBObject::instance()->res->next()) {
			//for (int i = 0; i < TotalNoOfSpots; i++)
			//{
				// Create parking space objects 
			pSpace.push_back(new ParkingSpace(100, 100, LotName, i + 1));
			//}
			i++;
		}
	}

public:
	string getLotName();

	int getTotalNoOfSpots();

	static LotJ* getInstance();

};

#endif