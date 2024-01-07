//
//  SpaceW.cc
//  
//
//  Created by Dami on 11/08/2023.
//

#include "SpaceW.h"



SpaceW::SpaceW() {}

SpaceW::~SpaceW() {
    for (size_t i = 0; i < rockets.getSize(); ++i) {
        delete rockets[i];
    }
    for (size_t i = 0; i < parts.getSize(); ++i) {
        delete parts[i];
    }
}

void SpaceW::addRocket(const string& name) {
    rockets.add(new Rocket(name));
}

void SpaceW::addPart(const string& name, const Date& manufacturing_date, int launch_threshold, int time_threshold) {
    Part* part = partFactory.createPart(name, manufacturing_date, launch_threshold, time_threshold);
    parts.add(part);
}

void SpaceW::installPart(const string& rocket_name, const string& part_name, const Date& installation_date) {
    Rocket* rocket = nullptr;
    Part* part = nullptr;

    for (int i = 0; i < rockets.getSize(); ++i) {
        if (rockets[i]->equals(rocket_name)) {
            rocket = rockets[i];
            break;
        }
    }

    for (int i = 0; i < parts.getSize(); ++i) {
        if (parts[i]->equals(part_name)) {
            part = parts[i];
            break;
        }
    }

    if (rocket && part) {
        rocket->install(part, installation_date);
    }
}

bool SpaceW::launch(const string& rocket_name, const Date& launch_date) {
    for (int i = 0; i < rockets.getSize(); ++i) {
        if (rockets[i]->equals(rocket_name)) {
            rockets[i]->launch(launch_date);
        }
        return true;
    }
    return false;
}

void SpaceW::inspect(const std::string& rocket_name, const Date& inspection_date) {
    for (int i = 0; i < rockets.getSize(); ++i) {
        
        if (rockets[i]->equals(rocket_name)) {
            Array<Part*> toInspect;
            rockets[i]->getPartsToInspect(inspection_date, toInspect);
            
            for (int j = 0; j < toInspect.getSize(); ++j) {
                toInspect[j]->inspect(inspection_date);
            }
            
        }
    }
}

void SpaceW::inspectionReport(const Date& current_date) {
    for (int i = 0; i < rockets.getSize(); ++i) {
        if (rockets[i]->needsInspection(current_date)) {
            cout << *rockets[i] << " requires inspection." << endl;
        }
    }
}

void SpaceW::printRockets() const {
    for (int i = 0; i < rockets.getSize(); ++i) {
        cout << *rockets[i] << endl;
    }
}

void SpaceW::printParts() const {
    for (int i = 0; i < parts.getSize(); ++i) {
        cout << *parts[i] << endl;
    }
}
