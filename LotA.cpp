#pragma once

#include "LotA.h"
#include <string>

LotA* LotA::a_instance = 0;
string LotA::getLotName()
{
	return LotName;
}
int LotA::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}
LotA* LotA::getInstance()
{
	if (!a_instance)
		a_instance = new LotA();
	return a_instance;
}
// !LOTA