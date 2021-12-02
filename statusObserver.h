#pragma once
#ifndef STATUSOBSERVER_H
#define STATUSOBSERVER_H

#include "DBObject.h"
#include "User.h"
#include "WidgetEditor.h"

class statusObserver
{
public:
	virtual void notify() = 0;
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
        DBObject::instance()->updateStatus("Unreserved", User::instance()->get_user());
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
        DBObject::instance()->updateStatus("Parked", User::instance()->get_user());
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
        DBObject::instance()->updateStatus("Reserved", User::instance()->get_user());
    }
    void updateUserObj()
    {
        User::instance()->set_status("Reserved");
        User::instance()->set_endTime(end_time);
        User::instance()->set_startTime(start_time);
        User::instance()->setReservedLot(lotName);
        User::instance()->setReservedSpot(newSpot);
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
    void setLocation(string Lot,string spot)
    {
        lotName = Lot;
        newSpot = spot;
    }
    void setTimes(string sTime, string eTime)
    {
        start_time = sTime;
        end_time = eTime;
    }
    wxWindow* wContext;
    string newSpot;
    string lotName;
    string start_time;
    string end_time;
};

#endif // !STATUSOBSERVER_H