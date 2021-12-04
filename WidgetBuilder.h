#pragma once
#ifndef WIDGETBUILDER_H
#define WIDGETBUILDER_H


#include <iostream>
#include <string>
#include "WidgetComposite.h"
#include <vector>
#include "wx/wx.h"

using namespace std;

class LotUI {
public:
    vector <WidgetComponent*> widgets;
    void ListParts()const {
        for (size_t i = 0; i < widgets.size(); i++) {
            
        }
    }
    void destroyParts() {
        for (auto p : widgets)
        {
            delete p;
        }
        widgets.clear();
    }
};

class LotBuilder {
public:
    virtual ~LotBuilder() {}
    virtual void ProduceTextField(TextField* text) const = 0;
    virtual void ProduceTextInput(TextInput* input) const = 0;
    virtual void ProduceTextButton(TextButton* textBtn) const = 0;
    virtual void ProducepngLogo(pngLogo* pngL) const = 0;
    virtual void ProducepngButton(pngButton* pngB) const = 0;
    virtual void producecomboBox(comboBox* combo) const = 0;
};

class ConcreteLotBuilder : public LotBuilder {
private:

    LotUI* product;
public:

    ConcreteLotBuilder() {
        this->Reset();
    }

    ~ConcreteLotBuilder() {
        delete product;
    }

    void Reset() {
        this->product = new LotUI();
    }
    void ProduceTextField(TextField* text) const override {
        this->product->widgets.push_back(text);
    }
    void ProduceTextInput(TextInput* input) const override {
        this->product->widgets.push_back(input);
    }
    void ProduceTextButton(TextButton* textBtn) const override {
        this->product->widgets.push_back(textBtn);
    }
    void ProducepngLogo(pngLogo* pngL) const override {
        this->product->widgets.push_back(pngL);
    }
    void ProducepngButton(pngButton* pngB) const override {
        this->product->widgets.push_back(pngB);
    }
    void producecomboBox(comboBox* combo) const override {
        if (combo->getName() == "endTimeBox")
        {
            combo->hideThis();
        }
        this->product->widgets.push_back(combo);
    }

    LotUI* GetProduct() {
       
        LotUI* result = this->product;
        this->Reset();
        return result;
    }
};

class Director {

private:
    LotBuilder* builder;
    wxWindow* windowContext;
    wxString lotName;
public:
    void set_builder(LotBuilder* builder, wxWindow* wContext, wxString lotN) {
        this->windowContext = wContext;
        this->builder = builder;
        this->lotName = lotN;
    }

    void BuildAlreadyReseved() {
        this->builder->ProduceTextField(new TextField(windowContext, wxID_ANY, "You have already reseved a spot \n         You cannot reserve more than one spot.", wxPoint(50, 180), wxSize(300, 70), "alreadyReservedMsg"));
    }

    void BuildFullProduct() {
        this->builder->ProduceTextField(new TextField(windowContext, wxID_ANY, "Time Start", wxPoint(80, 160), wxSize(70, 20), "sTime"));
        this->builder->ProduceTextField(new TextField(windowContext, wxID_ANY, "Time End", wxPoint(185, 160), wxSize(70, 20), "eTime"));
        this->builder->producecomboBox(new comboBox(windowContext, wxID_ANY, "1", wxPoint(80, 180), wxSize(70, 30), "startTimeBox"));
        this->builder->producecomboBox(new comboBox(windowContext, wxID_ANY, "0", wxPoint(180, 180), wxSize(70, 30), "endTimeBox"));
        this->builder->ProduceTextField(new TextField(windowContext, wxID_ANY, "         Set a time to reserve a spot", wxPoint(40, 210), wxSize(200, 30), "setReserveTimeText"));
        this->builder->ProduceTextButton(new TextButton(windowContext, 4, "Reserve Spot", wxPoint(75, 250), wxSize(150, 40), lotName));
    }

    void BuildPast6PM() {
        this->builder->ProduceTextField(new TextField(windowContext, wxID_ANY, "This lot is unavalable now: \n        Please come back tomorrow ", wxPoint(50, 180), wxSize(300, 70), "lateLotMsg"));
    }
    void BuildFullLot() {
         this->builder->ProduceTextField(new TextField(windowContext, wxID_ANY, "No spots left for \n                        Lot " + lotName, wxPoint(50, 180), wxSize(300, 70), "fullLotMsg"));
    }
};

#endif // !WIDGETBUILDER_H
