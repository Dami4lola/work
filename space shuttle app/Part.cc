//
//  Part.cc
//  
//
//  Created by Dami on 02/08/2023.
//

#include "Part.h"

// part fucntions
bool Part::equals(const string& name) const {
    return this->name == name;
}

void Part::inspect(const Date& d) {
    lastInspected = d;
    launches = 0;
}

void Part::launch() {
    launches++;
}

void Part::install(const string& rocket, const Date& d) {
    this->rocket = rocket;
    lastInspected = d;
}

ostream& operator<<(ostream& os, const Part& part) {
    part.print(os);
    return os;
}


//lt_part functions
LT_Part::LT_Part(const string& name, const Date& manufacturing_date, int launch_threshold)
    : launch_threshold(launch_threshold) {
    lastInspected = manufacturing_date;
        this->name = name;
}

bool LT_Part::needsInspection(const Date& current_date) const {
    return launches >= launch_threshold;
}

void LT_Part::print(ostream& os) const  {
    os << "Part Name: " << name << "\n"
       << "Rocket: " << rocket << "\n"
       << "Last Inspected: " << lastInspected << "\n"
       << "Launches: " << launches << "\n"
       << "Launch Threshold: " << launch_threshold << "\n";
}


//tt_paart functions
TT_Part::TT_Part(const string& name, const Date& manufacturing_date, int time_threshold)
    : time_threshold(time_threshold) {
    lastInspected = manufacturing_date;
        this->name = name;
}

bool TT_Part::needsInspection(const Date& current_date) const {
    Date inspection_date = lastInspected;
    inspection_date.addDays(time_threshold);
    return current_date >= inspection_date;
}

void TT_Part::print(ostream& os) const  {
    os << "Part Name: " << name << "\n"
       << "Rocket: " << rocket << "\n"
       << "Last Inspected: " << lastInspected << "\n"
       << "Launches: " << launches << "\n"
       << "Time Threshold: " << time_threshold << " days\n";
}


//lt_tt_part
LT_TT_Part::LT_TT_Part(const string& name, const Date& manufacturing_date, int launch_threshold, int time_threshold)
    : LT_Part(name, manufacturing_date, launch_threshold), TT_Part(name, manufacturing_date, time_threshold) {
    }

bool LT_TT_Part::needsInspection(const Date& current_date) const {
    return LT_Part::needsInspection(current_date) || TT_Part::needsInspection(current_date);
}

void LT_TT_Part::print(ostream& os) const  {
    os << "Part Name: " << name << "\n"
       << "Rocket: " << rocket << "\n"
       << "Last Inspected: " << lastInspected << "\n"
       << "Launches: " << launches << "\n"
       << "Launch Threshold: " << launch_threshold << "\n"
       << "Time Threshold: " << time_threshold << " days\n";
}

string Part::getName() const{
    return name;
}

void Part::setInstallationDate(const Date& installation_date) {
    this->lastInspected = installation_date;
}
