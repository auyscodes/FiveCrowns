//
// Created by nbhat on 9/16/2019.
//

#include "UI.h"


void UI::showMenu() {
    cout << "1. Save the game" << endl;
    cout << "2. Make a move" << endl;
    cout << "3. Ask for help" << endl;
    cout << "4. Quit the game" << endl;
}

void UI::showRoundState(Round* round) {

    cout << "Round Number: " << round->getRoundNumber() << endl;
//    for (auto  player: round->getPlayers()){
//        cout << player->getHand()->toString() << endl;
//    }
    map<string, Player*> players = round->getPlayers();
    map<string, Player*>::iterator it;
    for (it=players.begin();it!=players.end();it++){
        cout << it->first << " Hand : " << it->second->getHand()->toString() << endl;
    }
}

//void UI::showRoundState(Round &round) {
//    cout << round.getRoundNumber() <<endl;
//}

//void UI::showRoundState(Round* round) {
//    cout << round->getRoundNumber() << endl;
//}





