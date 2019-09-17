//
// Created by nbhat on 9/16/2019.
//

#include "CardPile.h"

CardPile *CardPile::getInstance() {
    if (instance==NULL){
        instance = new CardPile();
    }
    return instance;
}

CardPile* CardPile::instance = 0;

CardPile::CardPile() {

}
