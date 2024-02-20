#ifndef AEDSIMULATOR_H
#define AEDSIMULATOR_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <QString>

class AEDSimulator {
public:
    AEDSimulator();
    ~AEDSimulator();

    bool power();
    bool performSelfTest();
    bool analyzeHeartRhythm(QString);
    QString evaluateCPRQuality(int);

    int getBatteryPercent();
    void setBatteryPercent(int Percent);
    void replaceBattery();

    int getShockCount();
    void setShockCount(int);
    void increaseShockCount();

    int getPowerSwitch();

private:
    int battery_percent;
    std::string display_message;
    std::string audio;
    bool power_switch;
    int shockCount;
};

#endif // AEDSIMULATOR_H
