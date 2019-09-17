//
// Created by nbhat on 9/15/2019.
//

#include "DiscardPile.h"

DiscardPile *DiscardPile::getInstance() {
    if (instance == NULL){
        instance = new DiscardPile();
    }
    return instance;
}

DiscardPile* DiscardPile::instance = 0;

DiscardPile::DiscardPile() {

}
