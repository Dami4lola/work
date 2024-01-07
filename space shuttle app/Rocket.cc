//
//  Rocket.cc
//  
//
//  Created by Dami on 11/08/2023.
//

#include "Rocket.h"

Rocket::Rocket(const string& name) : name(name) {}

bool Rocket::equals(const string& name) const {
    return this->name == name;
}

bool Rocket::needsInspection(const Date& current_date) const {
    for (int i = 0; i < parts.getSize(); ++i) {
        if (parts[i]->needsInspection(current_date)) {
            return true;
        }
    }
    return false;
}

void Rocket::getPartsToInspect(const Date& current_date, Array<Part*>& toInspect) {
    for (int i = 0; i < parts.getSize(); ++i) {
        if (parts[i]->needsInspection(current_date)) {
            toInspect.add(parts[i]);
        }
    }
}

bool Rocket::install(Part* part, const Date& installation_date) {
    if(parts.isFull()){return false;}
    if (part) {
        parts.add(part);
        part->install(name, installation_date);
        return true;
    }
    return false;
}

bool Rocket::launch(const Date& launch_date) {
    if (needsInspection(launch_date)) {
        return false;
    }

    for (int i = 0; i < parts.getSize(); ++i) {
        parts[i]->launch();
    }
    return true;
}

ostream& operator<<(ostream& os, const Rocket& rocket) {
    os << "Rocket Name: " << rocket.name;
    return os;
}

