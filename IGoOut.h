//
// Created by nbhat on 9/23/2019.
//

#ifndef FIVECROWNS_IGOOUT_H
#define FIVECROWNS_IGOOUT_H

#include "Hand.h"

class IGoOut{
public:
    virtual void goOut(Hand* hand) = 0; // will be called when player goes out
};

#endif //FIVECROWNS_IGOOUT_H
