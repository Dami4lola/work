//
//  PartFactory.cc
//  
//
//  Created by Dami on 07/08/2023.
//

#include "PartFactory.h"


Part* PartFactory::createPart(const string& name, const Date& manufacturingDate, int launchThreshold, int timeThreshold) {
    if (launchThreshold == 0) {
        return new TT_Part(name, manufacturingDate, timeThreshold);
    } else if (timeThreshold == 0) {
        return new LT_Part(name, manufacturingDate, launchThreshold);
    } else {
        return new LT_TT_Part(name, manufacturingDate, launchThreshold, timeThreshold);
    }
}
