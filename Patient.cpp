#include "Patient.h"

Patient::Patient():cprCount(0), heartCondition(""){
}

int Patient::getCPRCount() const {
    return cprCount;
}

void Patient::setCPRCount(int count) {
    cprCount = count;
}

QString Patient::getHeartCondition(){
    return heartCondition;
}

void Patient::setHeartCondition(QString h){
    heartCondition = h;
}
