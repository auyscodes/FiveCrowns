//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_DISCARDPILE_H
#define FIVECROWNS_DISCARDPILE_H

#include <iostream>
#include "CardCollection.h"

class DiscardPile: public CardCollection {
public:
//    static DiscardPile* getInstance(){
//        if (instance == NULL){
//            instance = new DiscardPile();
//        }
//        return instance;
//    };
    static DiscardPile* getInstance();



private:

    DiscardPile();
    static DiscardPile * instance;
};


#endif //FIVECROWNS_DISCARDPILE_H
