#pragma once
#ifndef WIDGETCOMPOSITE_H
#define WIDGETCOMPOSITE_H
#include "wx/wx.h"
#include <vector>
using namespace std;
// common component for all the wxwidgets
class WidgetComponent
{
	public:
		// calls the wxwidgets destroy to delete an object
		virtual void destroy() = 0;
		// returns the objects name
		virtual wxString getName() = 0;
		// returns the relevent value for the object
		// input is the name of the object
		virtual wxString getValueByName(wxString name) = 0;
};
// for creating text fields
class TextField : public WidgetComponent
{
	wxStaticText* staticText;
	public:
		TextField(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, wxString name)
		{
			staticText = new wxStaticText(parent,id,label,pos,size);
			staticText->SetName(name);
		}
		~TextField()
		{
			destroy();
		}
		void destroy()
		{
			staticText->Destroy();
		}
		wxString getName()
		{
			return staticText->GetName();
		}
		wxString getValueByName(wxString name)
		{
			return staticText->GetLabel();
		}
};
// for creating text inputs
class TextInput : public WidgetComponent
{
	wxTextCtrl* textInput;
	public:
		TextInput(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, wxString name)
		{
			textInput = new wxTextCtrl(parent, id, label, pos, size);
			textInput->SetName(name);
		}
		TextInput(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, wxString name, wxString style)
		{
			if (style == "pass")
			{
				textInput = new wxTextCtrl(parent, id, label, pos, size, wxTE_PASSWORD);
			}
			else
			{
				textInput = new wxTextCtrl(parent, id, label, pos, size);
			}
			textInput->SetName(name);
		}
		~TextInput()
		{
			destroy();
		}
		void destroy()
		{
			textInput->Destroy();
		}
		wxString getName()
		{
			return textInput->GetName();
		}
		wxString getValueByName(wxString name)
		{
			return textInput->GetValue();
		}
};
// for creating buttons
class TextButton : public WidgetComponent
{
	wxButton* button;
	public:
		TextButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, wxString name)
		{
			button = new wxButton(parent, id, label, pos, size);
			button->SetName(name);
		}
		TextButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, wxString name, wxString style)
		{
			button = new wxButton(parent, id, label, pos, size);
			button->SetName(name);
			if (style == "hide")
			{
				button->Hide();
			}
		}
		~TextButton()
		{
			destroy();
		}
		void destroy()
		{
			button->Destroy();
		}
		wxString getName()
		{
			return button->GetName();
		}
		wxString getValueByName(wxString name)
		{
			return button->GetName();
		}
};
// for creating images
class pngLogo : public WidgetComponent
{
	wxStaticBitmap* png;
	public:
		pngLogo(wxWindow* parent, wxWindowID id, const wxGDIImage& label, const wxPoint& pos, const wxSize& size, wxString name)
		{
			png = new wxStaticBitmap(parent, id, label, pos, size);
			png->SetName(name);
		}
		~pngLogo()
		{
			destroy();
		}
		void destroy()
		{
			png->Destroy();
		}
		wxString getName()
		{
			return png->GetName();
		}
		wxString getValueByName(wxString name)
		{
			return png->GetName();
		}
};
// for creating buttons with images
class pngButton : public WidgetComponent
{
	wxBitmapButton* pngB;
public:
	pngButton(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos, const wxSize& size, wxString name)
	{
		pngB = new wxBitmapButton(parent, id, bitmap, pos, size);
		pngB->SetName(name);
	}
	~pngButton()
	{
		destroy();
	}
	void destroy()
	{
		pngB->Destroy();
	}
	wxString getName()
	{
		return pngB->GetName();
	}
	wxString getValueByName(wxString name)
	{
		return pngB->GetName();
	}
};
// for creating the dropdown menus
class comboBox : public WidgetComponent
{
	wxComboBox* combo;
public:
	comboBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, wxString name)
	{
		combo = new wxComboBox(parent, id, label, pos, size);
		combo->SetName(name);
	}
	~comboBox()
	{
		destroy();
	}
	void destroy()
	{
		combo->Destroy();
	}
	void hideThis()
	{
		combo->Hide();
	}
	wxString getName()
	{
		return combo->GetName();
	}
	wxString getValueByName(wxString name)
	{
		return combo->GetName();
	}
};
// holds a vector to contain groups of widgets so that i can add widgets more easily and destroy them all at once
class WidgetComposite : public WidgetComponent
{
	vector <WidgetComponent*> widgets;
	public:
		~WidgetComposite()
		{
			destroy();
		}
		void add(WidgetComponent* widget)
		{
			widgets.push_back(widget);
		}
		void destroy()
		{	
			for (auto p : widgets)
			{
				p->destroy();
				delete p;
			}
			widgets.clear();
		}
		int sizeOf()
		{
			return widgets.size();
		}
		wxString getName()
		{
			return "widgetComposite";
		}
		wxString getValueByName(wxString name)
		{
			for (size_t i = 0; i < widgets.size(); i++)
			{
				if (widgets[i]->getName() == name)
				{
					return widgets[i]->getValueByName(name);
				}
			}
		}
};
#endif // !WIDGETCOMPOSITE_H