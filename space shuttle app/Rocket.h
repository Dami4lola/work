//
//  Rocket.hpp
//  
//
//  Created by Dami on 11/08/2023.
//

#ifndef Rocket_h
#define Rocket_h

#include <stdio.h>
#include <string>
#include "Array.h"
#include "Part.h"
using namespace std;

class Rocket {
public:
    Rocket(const string& name);
    bool equals(const string& name) const;
    bool needsInspection(const Date& current_date) const;
    void getPartsToInspect(const Date& current_date, Array<Part*>& toInspect);
    bool install(Part* part, const Date& installation_date);
    bool launch(const Date& launch_date);
    friend ostream& operator<<(ostream& os, const Rocket& rocket);

private:
    string name;
    Array<Part*> parts;
};

#endif /* Rocket_h */
