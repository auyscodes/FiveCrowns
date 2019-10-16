//
// Created by nbhat on 10/13/2019.
//

#ifndef FIVECROWNS_COMPARECARDBYVALUE_H
#define FIVECROWNS_COMPARECARDBYVALUE_H

#include "CardInterface.h"
#include "Card.h"

class CompareCardByValue {
public:
    bool operator()( Card& card1,  Card& card2) const{
        return card1.getValue() < card2.getValue();
    }
};


#endif //FIVECROWNS_COMPARECARDBYVALUE_H
