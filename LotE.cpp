#pragma once

#include "LotE.h"
LotE* LotE::e_instance = 0;
string LotE::getLotName()
{
	return LotName;
}
int LotE::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

LotE* LotE::getInstance()
{
	if (!e_instance)
		e_instance = new LotE();
	return e_instance;
}
// !LotE