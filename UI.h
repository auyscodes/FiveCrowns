//
// Created by nbhat on 9/16/2019.
//

#ifndef FIVECROWNS_UI_H
#define FIVECROWNS_UI_H
class Round; // trying forward declaration since #including round was causing circular dependency error
#include <iostream>
#include "Round.h"
using namespace std;

class UI {
public:
    static void showMenu();
    static void showRoundState(Round* round);
};


#endif //FIVECROWNS_UI_H
