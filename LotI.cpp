#pragma once
#include "LotI.h"
LotI* LotI::i_instance = 0;
string LotI::getLotName()
{
	return LotName;
}
int LotI::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

LotI* LotI::getInstance()
{
	if (!i_instance)
		i_instance = new LotI();
	return i_instance;
}
// !LotI