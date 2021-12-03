#pragma once

#include "LotC.h"
LotC* LotC::c_instance = 0;
string LotC::getLotName()
{
	return LotName;
}
int LotC::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

 LotC* LotC::getInstance()
{
	if (!c_instance)
		c_instance = new LotC();
	return c_instance;
}
  //!LotC