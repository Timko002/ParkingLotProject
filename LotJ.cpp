#pragma once
#include "LotJ.h"
LotJ* LotJ::j_instance = 0;
string LotJ::getLotName()
{
	return LotName;
}
int LotJ::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
LotJ* LotJ::getInstance()
{
	if (!j_instance)
		j_instance = new LotJ();
	return j_instance;
}
// !LotJ