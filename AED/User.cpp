#include "User.h"

User::User() : compressionStrength(0), padsApplied(false) {}

bool User::getPadsApplied(){
    return padsApplied;
}

void User::setPadsApplied(bool p){
    padsApplied = p;
}

int User::getCompressionStrength(){
    return compressionStrength;
}

void User::setCompressionStrength(int strength){
    compressionStrength = strength;
}
