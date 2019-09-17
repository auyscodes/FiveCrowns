//
// Created by nbhat on 9/15/2019.
//

#include "DrawPile.h"

DrawPile *DrawPile::getInstance() {
    if (instance==NULL) {
        instance = new DrawPile();
    }
    return instance;
}

DrawPile* DrawPile::instance = 0;

DrawPile::DrawPile() {

}
