//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_DRAWPILE_H
#define FIVECROWNS_DRAWPILE_H


#include "CardCollection.h"

class DrawPile: public CardCollection {
public:
    static DrawPile* getInstance();

private:
    DrawPile();
    static DrawPile* instance;

};


#endif //FIVECROWNS_DRAWPILE_H
