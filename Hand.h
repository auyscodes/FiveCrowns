//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_HAND_H
#define FIVECROWNS_HAND_H


#include "CardCollection.h"

class Hand: public CardCollection {
};


#endif //FIVECROWNS_HAND_H

/*
 * Hand is not singleton because new hand must be created for every new player
 *
 *
 * Why can't we just use card collection instead of hand?
 *
 * */