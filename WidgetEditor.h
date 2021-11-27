#pragma once
#ifndef WIDGETEDITOR_H
#define WIDGETEDITOR_H
#include "wx/wx.h"

class WidgetEditor
{
public:
    wxWindow* getNode(wxWindow* wContext, wxString name)
    {
        wxWindowList& children = wContext->GetChildren();
        for (wxWindowList::Node* node = children.GetFirst(); node; node = node->GetNext())
        {
            wxWindow* current = (wxWindow*)node->GetData();
            if (current->GetName() == name)
            {
                // found the object
                return current;
            }
        }
        return NULL;
    }
    void changeLabel(wxWindow* wContext, wxString objectName, wxString label)
    {
        wxWindow* node = getNode(wContext, objectName);
        node->SetLabel(label);
    }
    void deleteItem(wxWindow* wContext, wxString objectName)
    {
        wxWindow* node = getNode(wContext, objectName);
        delete node;
    }
    wxStaticText* generatePointerSText(wxWindow* node)
    {
        if (dynamic_cast<wxStaticText*>(node)) {
            return dynamic_cast<wxStaticText*>(node);
        }
        else
        {
            return nullptr;
        }
    }
    wxComboBox* generatePointerCombo(wxWindow* node)
    {
        if (dynamic_cast<wxComboBox*>(node)) {
            return dynamic_cast<wxComboBox*>(node);
        }
        else
        {
            return nullptr;
        }
    }
};
#endif // !WIDGETEDITOR_H
