//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_GAME_H
#define FIVECROWNS_GAME_H


#include "Player.h"
#include "DataLayer.h"
#include "ISave.cpp"
#include <map>
class Game: public Save{
public:
	Game();
    void start();
	bool saveGame(string filename);
	void startNew();
	void loadGame(string filename);
private:
    int numRounds = 11;
    int startingAtRound = 1;
    DataLayer* dataLayer;
     vector<Player*>* createPlayers(int& startPlayerIndex, int&humanPlayerIndex, int&computerPlayerIndex);
	void displayWinnerAndLoserScore();
	static int toss(int humanPlayerIndex, int computerPlayerIndex, int totalPlayers);
	void askUser();
};


#endif //FIVECROWNS_GAME_H
