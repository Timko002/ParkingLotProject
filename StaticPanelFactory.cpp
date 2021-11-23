#pragma once

#include "StaticPanelFactory.h"

Panel* StaticPanelFactory::makePanel(string name)
{
	Panel* panel;
	if (name == "login")
	{
		panel = new LoginPanel();
	}
	else
	{
		panel = NULL;
	}
	return panel;
}