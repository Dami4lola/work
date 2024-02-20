#include "AEDSimulator.h"
#include <iostream>
#include <QtDebug>

AEDSimulator::AEDSimulator() : battery_percent(100), power_switch(false), shockCount(0) {
}

AEDSimulator::~AEDSimulator() {}

bool AEDSimulator::power() {
    if (power_switch == false) {
        power_switch = true;
        return true;
    } else {
        power_switch = false;
        return false;
    }
}

bool AEDSimulator::performSelfTest() {
    if(battery_percent <= 20){
        return false;
    }
    qInfo("Unit OK.");
    return true;
}

//Decides whether or not the patients heart rhythm returns to normal. Asystole can po
bool AEDSimulator::analyzeHeartRhythm(QString heart_rhythm) {
    if(heart_rhythm == "asystole"){
        return false;
    }else{
        srand(time(NULL));

        if(rand() % 3 == 0){
            return true;
        }else{
            return false;
        }
    }
}

QString AEDSimulator::evaluateCPRQuality(int compression_strength){
    if(compression_strength == 0){
        return "CONTINUE CPR";
    }else if(compression_strength < 85){
        return "PUSH HARDER";
    }else{
        return "GOOD COMPRESSIONS";
    }
}

int AEDSimulator::getBatteryPercent() {
    return battery_percent;
}

void AEDSimulator::setBatteryPercent(int Percent){
    battery_percent = Percent;
}

void AEDSimulator::replaceBattery(){
    setBatteryPercent(100);
}

int AEDSimulator::getShockCount(){
    return shockCount;
}

void AEDSimulator::setShockCount(int count){
    shockCount = count;
}

void AEDSimulator::increaseShockCount(){
    shockCount++;
}

int AEDSimulator::getPowerSwitch(){
    return power_switch;
}
