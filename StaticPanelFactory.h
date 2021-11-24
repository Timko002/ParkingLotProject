#pragma once
#ifndef STATICPANELFACTORY_H
#define STATICPANELFACTORY_H
#include <string>
#include "LoginPanel.h"
#include "MapPanel.h"
#include "LotPanel.h"

class StaticPanelFactory
{
	public:
		static Panel* makePanel(string name)
		{
			Panel* panel;
			if (name == "login")
			{
				panel = new LoginPanel();
			}
			else if (name == "map")
			{
				panel = new MapPanel();
			}
			else if (name == "lot")
			{
				panel = new LotPanel();
			}
			else
			{
				panel = NULL;
			}
			return panel;
		}
};

#endif // !STATICPANELFACTORY_H