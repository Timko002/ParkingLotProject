#pragma once
#include "LotH.h"
LotH* LotH::h_instance = 0;
string LotH::getLotName()
{
	return LotName;
}
int LotH::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

LotH* LotH::getInstance()
{
	if (!h_instance)
		h_instance = new LotH();
	return h_instance;
}

// !LotH