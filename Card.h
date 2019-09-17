//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_CARD_H
#define FIVECROWNS_CARD_H


#include <iostream>
#include <string>
#include "CardInterface.h"

using namespace std;

class Card: public CardInterface{
public:
    string toString();
    string getFace();
    string getSuit();
    void setFace(string face);
    void setSuit(string suit);



};
#endif //FIVECROWNS_CARD_H
