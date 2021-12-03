#pragma once
#include "LotF.h"
LotF* LotF::f_instance = 0;
string LotF::getLotName()
{
	return LotName;
}
int LotF::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

LotF* LotF::getInstance()
{
	if (!f_instance)
		f_instance = new LotF();
	return f_instance;
}
// !LotF