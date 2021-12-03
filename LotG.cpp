#pragma once
#include "LotG.h"
LotG* LotG::g_instance = 0;
string LotG::getLotName()
{
	return LotName;
}
int LotG::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

LotG* LotG::getInstance()
{
	if (!g_instance)
		g_instance = new LotG();
	return g_instance;
}
// !LotG