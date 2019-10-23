//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_GAME_H
#define FIVECROWNS_GAME_H


#include "Player.h"
#include "DataLayer.h"
#include "ISave.cpp"
#include <map>

/*
	Entry point for game.

*/
class Game: public Save{
public:
	/*
		Constructor for creating game class.
		Initializes dataLayer member variable as null
		dataLayer is dependent on input of the user
	*/
	Game();
	/*
		Provides user the option of loading a game or starting new.
		Displays score at the end, i.e. if the player plays the game until the end

	*/
    void start();

	/*
		Saves the game state in a specific format
		Implementation of ISave.h class's pure virtual function so that player can callback the function
		@param filename used by ostream class to determine file's location
		@return true if successfully saved
	*/
	bool saveGame(string filename);
	/*
		Starts a new Game
	*/
	void startNew();
	/*
		Loads the game stored in file
		@param filename used by ostream class to determine file's location
	*/
	void loadGame(string filename);
	/*
		Destructor 
		Deletes DataLayer that was initialized
	*/
	~Game();
private:
    const int numRounds = 11; // number of rounds in game
	// starting round is 1  not 0

    DataLayer* dataLayer; // used for storing data that persists throughout the scope of the game

	/*
		Creates vector of player objects in heap
		@param startPlayerIndex to determine who calls the toss first
		@param humanPlayerIndex index of the human player in the vector returned
		@param computerPlayerIndex index of the computer player in the vector returned
		@return collection of players
	*/
    vector<Player*>* createPlayers(int& startPlayerIndex, int&humanPlayerIndex, int&computerPlayerIndex);

	/*
		Outputs draw if both the players have same score
		Outputs Human has won if the human player has lower score
		Outputs Computer has won if the computer player has lower score
	*/
	void displayWinnerAndLoserScore();
	/*
		Generates random number  0(tail) or 1(head) to determine first player
		@param humanPlayerIndex player's index of collection in datalayer
		@param computerPlayerIndex player's index of collection in datalayer
		@return player's index that determines who starts first
	*/
	int toss(int humanPlayerIndex, int computerPlayerIndex);

	/*
		Asks the user whether to start a new game or load game
	*/
	void askUser();
};


#endif //FIVECROWNS_GAME_H
