//
//  Part.h
//  
//
//  Created by Dami on 02/08/2023.
//

#ifndef Part_h
#define Part_h

#include <stdio.h>
#include <iostream>
#include <string>
#include "Date.h"

using namespace std;


class Part {
public:
    virtual ~Part() = default;

    bool equals(const string& name) const;
    void inspect(const Date& d);
    void launch();
    void install(const string& rocket, const Date& d);
    virtual bool needsInspection(const Date& current_date) const = 0;
    virtual void print(ostream& os) const = 0;
    string getName() const;

    friend ostream& operator<<(ostream& os, const Part& part);
    void setInstallationDate(const Date& installation_date);

protected:
    string name;
    string rocket;
    Date lastInspected;
    int launches;
};
ostream& operator<<(ostream& os, const Part& part);


class LT_Part : public virtual Part {
public:
    LT_Part(const string& name, const Date& manufacturing_date, int launch_threshold);
    bool needsInspection(const Date& current_date) const override;
    void print(ostream& os) const override;


protected:
    int launch_threshold;
};



class TT_Part : public virtual Part {
public:
    TT_Part(const string& name, const Date& manufacturing_date, int time_threshold);
    bool needsInspection(const Date& current_date) const override;
    void print(ostream& os) const override;


protected:
    int time_threshold;
};


class LT_TT_Part : public LT_Part, public TT_Part {
public:
    LT_TT_Part(const string& name, const Date& manufacturing_date, int launch_threshold, int time_threshold);
    bool needsInspection(const Date& current_date) const override;
    void print(ostream& os) const override;

};


#endif /* Part_h */
