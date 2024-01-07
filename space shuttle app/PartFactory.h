//
//  PartFactory.h
//  
//
//  Created by Dami on 07/08/2023.
//

#ifndef PartFactory_h
#define PartFactory_h

#include <stdio.h>
#include "Part.h"


class PartFactory {
public:
    Part* createPart(const string& name, const Date& manufacturingDate, int launchThreshold, int timeThreshold);
};

#endif /* PartFactory_h */
