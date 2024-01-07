//
//  SpaceW.h
//  
//
//  Created by Dami on 11/08/2023.
//

#ifndef SpaceW_h
#define SpaceW_h

#include <stdio.h>
#include <string>
#include <iostream>
#include "Array.h"
#include "Rocket.h"
#include "PartFactory.h"

using namespace std;

class SpaceW {
public:
    SpaceW();
    ~SpaceW();
    void addRocket(const string& name);
    void addPart(const string& name, const Date& manufacturing_date, int launch_threshold, int time_threshold);
    void installPart(const string& rocket_name, const string& part_name, const Date& installation_date);
    bool launch(const string& rocket_name, const Date& launch_date);
    void inspect(const string& rocket_name, const Date& inspection_date);
    void inspectionReport(const Date& current_date);
    void printRockets() const;
    void printParts() const;

private:
    Array<Rocket*> rockets;
    Array<Part*> parts;
    PartFactory partFactory;
};

#endif /* SpaceW_h */
