#pragma once
#ifndef STATUSOBSERVER_H
#define STATUSOBSERVER_H

#include "DBObject.h"
#include "User.h"
#include "WidgetEditor.h"
// common observer interface
class statusObserver
{
public:
	virtual void notify() = 0;
};
// a task list to update the user singleton,  database and then UI
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
// alert for leaving a spot
class leaveSpot : public statusUpdate, public statusObserver
{
    void updateUI()
    {
        WidgetEditor edit;
        edit.changeLabel(wContext, "statusField", "Status: " + User::instance()->get_status() + " | ");
        edit.changeLabel(wContext, "spotLocation", "");
        edit.changeLabel(wContext, "bookedTime", "");
    }
    void updateDB()
    {
        DBObject::instance()->updateStatus("Unreserved", User::instance()->get_user());
    }
    void updateUserObj()
    {
        User::instance()->set_status("Unreserved");
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
// alert for parked
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
// alert for registering a new spot
class registerUpdate : public statusUpdate, public statusObserver
{
    void updateUI()
    {
        WidgetEditor edit;
        edit.changeLabel(wContext, "statusField", "Status: " + User::instance()->get_status() + " | ");
        edit.changeLabel(wContext, "spotLocation", "Location: Lot" + User::instance()->getReservedLot() + " | " + "Spot" + User::instance()->getReservedSpot());
        edit.changeLabel(wContext, "bookedTime", "Reserved Time : " + User::instance()->get_startTime() + "~" + User::instance()->get_endTime());
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