#pragma once
#ifndef WIDGETCOMPOSITE_H
#define WIDGETCOMPOSITE_H
#include "wx/wx.h"
#include <vector>
using namespace std;

class WidgetComponent
{
	public:
		virtual void destroy() = 0;
};

class TextField : public WidgetComponent
{
	wxStaticText* staticText;
	public:
		TextField(wxStaticText* text)
		{
			staticText = text;
		}
		void destroy()
		{
			staticText->Destroy();
		}
};
class TextInput : public WidgetComponent
{
	wxTextCtrl* textInput;
	public:
		TextInput(wxTextCtrl* textCtrl)
		{
			textInput = textCtrl;
		}
		void destroy()
		{
			textInput->Destroy();
		}
};
class TextButton : public WidgetComponent
{
	wxButton* button;
	public:
		TextButton(wxButton* buttonPtr)
		{
			button = buttonPtr;
		}
		void destroy()
		{
			button->Destroy();
		}
};

class pngLogo : public WidgetComponent
{
	wxStaticBitmap* png;
	public:
		pngLogo(wxStaticBitmap* logo)
		{
			png = logo;
		}
		void destroy()
		{
			png->Destroy();
		}
};

class WidgetComposite : public WidgetComponent
{
	vector <WidgetComponent*> widgets;
	public:
		void add(WidgetComponent* widget)
		{
			widgets.push_back(widget);
		}
		void destroy()
		{
			for (int i = 0; i < widgets.size(); i++)
			{
				widgets[i]->destroy();
			}
		}
};
#endif // !WIDGETCOMPOSITE_H