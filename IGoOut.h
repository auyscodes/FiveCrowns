//
// Created by nbhat on 9/23/2019.
//

#ifndef FIVECROWNS_IGOOUT_H
#define FIVECROWNS_IGOOUT_H

#include "Hand.h"
// tries to go out
// if successful going out occurs returns true
// otherwise returns false
class IGoOut{
public:


    virtual bool tryGoOut(Hand* hand, int& minScore, vector<vector<CardInterface*>>&minBranch) = 0; // will be called when player goes out
};

#endif //FIVECROWNS_IGOOUT_H
