#ifndef USER_H
#define USER_H

#include <string>
#include <stdio.h>
#include <iostream>

class User {
public:
    User();

    bool getPadsApplied();
    void setPadsApplied(bool);

    int getCompressionStrength();
    void setCompressionStrength(int strength);

private:
    int compressionStrength;
    bool padsApplied;
};

#endif // USER_H
