#pragma once
#ifndef STATICPANELFACTORY_H
#define STATICPANELFACTORY_H
#include <string>
#include "LoginPanel.h"
#include "MapPanel.h"

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
			else
			{
				panel = NULL;
			}
			return panel;
		}
};

#endif // !STATICPANELFACTORY_H