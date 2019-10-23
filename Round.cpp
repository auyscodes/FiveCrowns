//
// Created by nbhat on 9/15/2019.
//

#include "Round.h"
#include "DataLayer.h"



Round::Round(DataLayer* dataLayer) {

	this->numCardsToDeal = dataLayer->getRound() + 2;
	this->dataLayer = dataLayer;

}

void Round::deal() {


   /* DrawPile* drawPile = DrawPile::getInstance();
    DiscardPile* discardPile = DiscardPile::getInstance();
    CardPile* cardCollection = CardPile::getInstance();*/

    // if discardPile isEmpty then it is a new game
    //if (discardPile->isEmpty()){
    //    // If it is a first round then builds a deck and adds to a cardcollection.
    //    if (numCardsToDeal - 2 == startRound) {

    //        Deck deck1 = Deck::Builder().numericFace(3, 9).specialFace({"J", "Q", "K", "X"}).suits(
    //                {"C", "H", "D", "S", "T"}).joker(3).build();
    //        deck1.shuffle();
    //        Deck deck2 = Deck::Builder().numericFace(3, 9).specialFace({"J", "Q", "K", "X"}).suits(
    //                {"C", "H", "D", "S", "T"}).joker(3).build();
    //        deck2.shuffle();


    //        cardCollection->collect(&deck1);
    //        cardCollection->collect(&deck2);
    //        cardCollection->shuffle();
    //    }
    //    
		

    //    for (int i=0;i<numCardsToDeal;i++){

    //        for (auto player: *dataLayer->getPlayers()){
    //            player->setCard(cardCollection->popFront());
    //        }
    //    }

    //    drawPile->collect(cardCollection);
    //    discardPile->addFront(drawPile->popFront());


    //}
	
	CardPile* cardCollection = dataLayer->getCardPile();
	// this means player started a new game 
	cardCollection->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		
	for (int i=0;i<numCardsToDeal;i++){

		for (auto player: *dataLayer->getPlayers()){
             player->setCard(cardCollection->popFront());
        }
	}
	dataLayer->getDrawPile()->collect(cardCollection);
	dataLayer->getDisCardPile()->addFront(dataLayer->getDrawPile()->popFront());

	


}



void Round::collectCardsFromPiles(){

	CardPile* cardCollection = dataLayer->getCardPile();


    cardCollection->collect(dataLayer->getDrawPile());
    cardCollection->collect(dataLayer->getDisCardPile());


    for (auto player:*dataLayer->getPlayers()){
        cardCollection->collect(player->getHand());
    }
	
    cardCollection->shuffle();

}





// checks if go out success. if success increases players gone out count, notifies other players and returns true
// otherwise returns false
bool Round::tryGoOut(Hand* hand, int& score, vector<vector<CardInterface*>>& cardsArrgnmnt) {
	Hand new_hand = *hand; // so that hand is copied and not modified
		if (checkGoOutPossible(&new_hand, score, cardsArrgnmnt)) {
			/*cout << "Inside rounds try go out " << endl;

			cout << "score : " << score << endl;
			
			cout << "Cards Arrangement : ";
			tempPrinter(cardsArrgnmnt);*/

			this->playersGoneOut++;
			notifyOtherPlayers(this->dataLayer->getPlayers());
			return true;
		}
		return false;
	
}




void Round::tempPrinter(vector < vector<CardInterface*>> & cardsArrgnment) {
	cout << " [ ";
	for (auto elem : cardsArrgnment) {
		cout << " [ ";
		for (auto e : elem) {
			cout << e->toString() << " ";
		}
		cout << " ] ";
	}
	cout << " ] ";
}

// right now notifies all the players even the  one that just go out
void Round::notifyOtherPlayers(vector<Player*>* players) {
	vector<Player*>& playersRef = *players;
	for (int i = 0; i < players->size(); i++) {
		Player* player = playersRef[i];
		player->playerGoOut(true);
	}
}


void Round::forceGoOut(CardCollection* hand, int&score, vector<vector<CardInterface*>>& branch)
{
	CardCollection new_hand = *hand; // so that hand is copied and not modified 

	new_hand.minScoreAndBranch(score, branch);
	this->playersGoneOut++;
	notifyOtherPlayers(this->dataLayer->getPlayers());

}



int Round::getScore(Card* card){
    if (card->getSuit()=="J") return 50;
    if (card->isWildCard()) return 20;

    if (card->getFace() == "3") return 3;
    if (card->getFace() == "4") return 4;
    if (card->getFace() == "5") return 5;
    if (card->getFace() == "6") return 6;
    if (card->getFace() == "7") return 7;
    if (card->getFace() == "8") return 8;
    if (card->getFace() == "9") return 9;
    if (card->getFace() == "X") return 10;
    if (card->getFace() == "J") return 11;
    if (card->getFace() == "Q") return 12;
    if (card->getFace() == "K") return 13;

}
// change this function name to determine face of wildcard
string Round::convertNumCardsToDealToWildCards(int numCardsToDeal) {
    if (numCardsToDeal <= 9) return to_string(numCardsToDeal);
	if (numCardsToDeal == 10) return "X";
    if (numCardsToDeal == 11) return "J";
    if (numCardsToDeal == 12) return "Q";
    if (numCardsToDeal == 13) return "K";
}


bool Round::checkGoOutPossible(CardCollection *hand, int& score, vector<vector<CardInterface*>>&minBranch) {
	
	
	if (hand->isGoingOutPossible(score, minBranch)) {
		return true; 
	}
    return false;
}


void Round::startGame() {

	cout << "-----------------------" << "Round " << dataLayer->getRound() << "-----------------------------" << endl;
	if (!dataLayer->isLoad()) {
		deal();
	}
	if (dataLayer->isLoad()) {
		cout << "loading game " << endl;
		// need to transform all the cards to wilcards

		vector<Player*>* players = dataLayer->getPlayers();
		Player* player1 = players->front();
		Player* player2 = players->back();
		CardCollection* p1hand = player1->getHand();
		p1hand->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		CardCollection* p2hand = player2->getHand();
		p2hand->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		

		CardCollection* drawPile = dataLayer->getDrawPile();
		CardCollection* discardPile = dataLayer->getDisCardPile();
		drawPile->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		drawPile->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		
		
	}
	

	cout << "DrawPile: " << DrawPile::getInstance()->toString() << endl;
	cout << "DiscardPile: " << DiscardPile::getInstance()->toString() << endl;

	for (auto player : *dataLayer->getPlayers()) {

		cout << "\n\t\tname : " << player->getName() << endl;
		cout << "\n\t\thand : " << player->getHand()->toString() << endl;
		cout << "\n\t\tscore : " << player->getScore() << endl;

	}



	int nextPlayerIndex = dataLayer->getNextPlayerIndex();
	int totalNumberOfPlayers = dataLayer->getPlayers()->size();


	cout << "totalNumberOfPlayers : " << totalNumberOfPlayers << endl;
	// cout << "playersGoneOut : " << playersGoneOut << endl;

	while (playersGoneOut < totalNumberOfPlayers) {
		auto nextPlayer = (*dataLayer->getPlayers())[nextPlayerIndex];

		cout << "Next Player : " << nextPlayer->getName() << endl;

		bool goOutFlag = nextPlayer->playGame();

		if (this->playersGoneOut > 0) {
			vector<vector<CardInterface*>> arrgnmnt;
			int score;
			forceGoOut(nextPlayer->getPlayerHand(), score, arrgnmnt);
			nextPlayer->addToScore(score);


			cout << "Player gone out " << endl;
			cout << "Arragement of cards while going out : ";
			this->tempPrinter(arrgnmnt);
			cout << "Score Player received : " << score << endl;



		}

		if (goOutFlag && playersGoneOut == 0) {
			vector<vector<CardInterface*>> arrgnmnt;
			int score;
			bool successful = tryGoOut(nextPlayer->getPlayerHand(), score, arrgnmnt);
			if (successful) {
				nextPlayer->addToScore(score);


				cout << "Player successfully gone out " << endl;
				cout << "Arragement of cards while going out : ";
				this->tempPrinter(arrgnmnt);
				cout << "Score Player received : " << score << endl;


			}
			else {

				cout << "!!! Going out was not possible " << endl;
			}
		}

		nextPlayerIndex = (++nextPlayerIndex) % (*dataLayer->getPlayers()).size();
		dataLayer->setNextPlayerIndex(nextPlayerIndex);


		/*cout << "***********************Score after each Player's turn*********************** " << endl;
		cout << "score of human : " << dataLayer->getPlayers()->at(dataLayer->getHumanPlayerIndex())->getScore() << endl;
		cout << "score of computer: " << dataLayer->getPlayers()->at(dataLayer->getComputerPlayerIndex())->getScore() << endl;;
		cout << "*********************************************************" << endl;*/
	}


	cout << "--------------------------------------------------------------------------------" << endl;


	for (auto player : *dataLayer->getPlayers()) {
		player->playerGoOut(false); // cleared at round end
	}
	// collects cards at the end of every round and puts it in the card collection
	collectCardsFromPiles();
	dataLayer->getCardPile()->undoCardsTmation();
	dataLayer->turnIsLoadOff();

}




