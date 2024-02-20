#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <QString>

class Patient {
public:
    Patient();

    int getCPRCount() const;
    void setCPRCount(int count);

    QString getHeartCondition();
    void setHeartCondition(QString);

private:
    int cprCount;
    QString heartCondition;
};

#endif // PATIENT_H
