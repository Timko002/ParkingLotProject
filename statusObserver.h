#pragma once
#ifndef STATUSOBSERVER_H
#define STATUSOBSERVER_H

#include "DBObject.h"
#include "User.h"
#include "WidgetEditor.h"

class statusObserver
{
public:
	virtual void notify(wxWindow* context) = 0;
};

class statusUpdate
{
    virtual void updateUI()
    {
      
    }
    virtual void updateDB()
    {
        
    }
    virtual void updateUserObj()
    {
     
    }
public:
    void updating()
    {
        updateUserObj();
        updateDB();
        updateUI();
    }
};

class leaveSpot : public statusUpdate, public statusObserver
{
    void updateUI()
    {
        WidgetEditor edit;
        edit.changeLabel(wContext, "statusField", "Status: " + User::instance()->get_status() + " | ");
        edit.changeLabel(wContext, "spotLocation", "");
    }
    void updateDB()
    {
        //DBObject::instance()->supdateStatus("Unreserved")
    }
    void updateUserObj()
    {
        User::instance()->set_status("UnReserved");
    }
public:
    void notify()
    {
        updating();
    }
    void setContext(wxWindow* context)
    {
        wContext = context;
    }
    wxWindow* wContext;
};

class parkedUpdate : public statusUpdate, public statusObserver
{
    void updateUI()
    {
        WidgetEditor edit;
        edit.changeLabel(wContext, "statusField", "Status: " + User::instance()->get_status() + " | ");
    }
    void updateDB()
    {
        //DBObject::instance()->supdateStatus("Parked")
    }
    void updateUserObj()
    {
        User::instance()->set_status("Parked");
    }
public:
    void notify()
    {
        updating();
    }
    void setContext(wxWindow* context)
    {
        wContext = context;
    }
    wxWindow* wContext;
};

class registerUpdate : public statusUpdate, public statusObserver
{
    void updateUI()
    {
        WidgetEditor edit;
        edit.changeLabel(wContext, "statusField", "Status: " + User::instance()->get_status() + " | ");
        edit.changeLabel(wContext, "spotLocation", "Location: Lot" + User::instance()->getReservedLot() + " | " + "Spot" + User::instance()->getReservedSpot());
    }
    void updateDB()
    {
        //DBObject::instance()->supdateStatus("Reserved")
    }
    void updateUserObj()
    {
        User::instance()->set_status("Reserved");
    }
public:
    void notify()
    {
        updating();
    }
    void setContext(wxWindow* context)
    {
        wContext = context;
    }
    wxWindow* wContext;
};

#endif // !STATUSOBSERVER_H