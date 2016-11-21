#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h> //rand and srand
#include<time.h> //time

enum score {NOTHING, PAIR, DOUBLE, TRIPLE, STRAIT, FLUSH, FULLHOUSE, FOURKIND, STRAITFLUSH, ROYAL};

enum value {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

enum suit {HEARTS=1, DIAMONDS, CLUBS, SPADES};

using namespace std;

score Score = NOTHING;

switch(Score){
case score::NOTHING :
	cout<<"Nothing"<<endl;
	break;
case score::PAIR :
	cout<<"Pair of"<<endl;
}

int valueOfPref = 0;

class Card {
public:
   int value;
   int suit;

   Card(int v, int s) {
       value = v;
       suit = s;
   }
};

vector<Card*> cards;

class Deck{
public:

	void printDeck();
	void shuffle();

    Deck() {
        cout<<"Deck Being Created"<<endl;
        //Creates the cards and inserts them into the Deck

        for(int i=1; i<5; i++) {
            for(int j=2; j<15; j++) {
            	cards.push_back(new Card(j, i));
            }
        }
        cout<<"Deck Created"<<endl;
    }
};

class Hand {

public:
	vector<Card*> hand;

	void replaceHand();
	void sortHand();
	void sortHandValue(); //sorts hand by value

	Hand() {
		for(int i = 0; i<5; i++) {
			hand.insert(hand.begin(), cards[0]);
			cards.erase(cards.begin());
		}
	}
};

void startGame();

void toLower(string);

int getScore(Hand);
void rankPlayers();

void printHand(Hand);

vector<Hand*> players;

int main() {


	startGame();

	return 0;
}

void Deck::printDeck() {
	for(int i = 0; i<cards.size(); i++) {
		cout<<cards[i]->value<<" of "<<cards[i]->suit<<endl;
	}
}

void Deck::shuffle() {
	srand(time(NULL));
	for(int i = 0; i<100; i++) {
		int random = rand() %52;
		cards.insert(cards.begin()+random, cards[0]);
		cards.erase(cards.begin());
	}
}

void Hand::sortHand() {
	for(int i = 0; i<4; i++) {
		for(int j = i+1; j<5; j++) {
			if(hand[i]->suit > hand[j]->suit) {
				hand.insert(hand.begin()+j+1, hand[i]);
				hand.erase(hand.begin()+i);
				if(i>0)
					i--;
			}
		}
	}

	for(int i = 0; i<4; i++) {
		for(int j = i+1; j<5; j++) {
			if(hand[i]->suit==hand[j]->suit && hand[i]->value > hand[j]-> value) {
				hand.insert(hand.begin()+j+1, hand[i]);
				hand.erase(hand.begin()+i);
				if(i>0)
					i--;
			}
		}
	}
}

void Hand::sortHandValue() {
	for(int i = 0; i<4; i++) {
		for(int j = i+1; j<5; j++) {
			if(hand[i]->value > hand[j]->value) {
				hand.insert(hand.begin()+j+1, hand[i]);
				hand.erase(hand.begin()+i);
				if(i>0)
					i--;
			}
		}
	}
}

int getHighCard(Hand h) {
	int HighCard = 0;
	for(int i = 0; i<4; i++) {
		if(h.hand[i]->value>HighCard) {
			HighCard = h.hand[i]->value;
		}
	}
	return HighCard;
}

int getScore(Hand h) {
	int score=9;
	int checker = 0;
	int checker2 = 0;
	int i = 0;
	bool isBreak = false;
	while(isBreak == false) {
		if(score==9) { //royal flush, straitflush, flush and strait
			cout<<"Loop 9 Entered"<<endl;
			checker = 0;
			while(i<4 && h.hand[i]->value==h.hand[i+1]->value+1) {
				checker++;
				i++;
			}
			while(i<4 && h.hand[i]->suit == h.hand[i+1]->suit) {
				checker2++;
				i++;
			}

			if(checker==5){ //checks to see if all of the cards are in order
				if(h.hand[0]->value!=10) //if can't be royal flush
					score--;
				else if(checker2!=5) //if all card's suits aren't the same, but is a sequence
					score=4;
				isBreak=true;
			}
			else if(checker2==5) { //if all the cards suits are the same, but is not a sequence
				score=5;
			}
			else {
				score-=2;
				i=0;
			}
		}
		else if(score==7) { //four of a kind, three of a kind, full house, pair and two pair
			checker = 0;
			while(i<4&&h.hand[i]->value==h.hand[i+1]->value) {
				checker++;
				i++;
			}

			if(checker==3) {
				if(h.hand[0]->value==h.hand[3]->value||h.hand[1]->value==h.hand[4]->value) {}
				else
					score=6;
			}
			else if(checker==2) {
				if(h.hand[0]->value==h.hand[2]->value||h.hand[1]->value==h.hand[3]->value||h.hand[2]->value==h.hand[4]->value)
					score=3;
				else
					score=2;
			}
			else if(checker==1)
				score=1;
			else {
				score=0;
				//isBreak = true; //delete later
			}
			isBreak = true;
		}
	}
	return score;
}

//prints hand h to console
void printHand(Hand h) {
	for(int i = 0; i<5; i++ ){
		cout<<h.hand[i]->value<<" of "<<h.hand[i]->suit<<endl;
	}
	cout<<endl<<"-x-"<<endl<<endl;
}

void startGame() {
	Deck d;
	d.shuffle();
	//d.printDeck();

	int playNum; //number of players
	bool cont = true; //true if player wants to continue

	string input;
	//Hand a;

	do {
		cout<<"Do you want to play a game?"<<endl;
		cin>>input;
		toLower(input);
		int valueScore = 0;
		if(input=="yes"||input=="y") {
		}
		else {
			cont = false;
			break;
		}
		vector<int> rank; //the number of the player
		cout<<"How many players?"<<endl;
		cin>>playNum;
		for(int i = 0; i<playNum; i++) {
			players.push_back(new Hand());
			cout<<"Player "<<i+1<<": "<<endl;
			players[i]->sortHandValue();
			players[i]->sortHandValue();
			printHand(*players[i]);
			valueScore = getScore(*players[i]);
			cout<<getScore(*players[i])<<endl;
			if(valueScore==0)
				cout<<"High Card: "<<getHighCard(*players[i])<<endl;
			else {

			}
			cout<<endl;
		}
		rankPlayers();
		for(int i = 0; i<players.size(); i++) {
			cout<<"Player "<<rank[i]<<endl;
		}
	}while(cont == true);
}

void rankPlayers() {
	for(int i = 0; i<players.size()-1; i++) {
		if(getScore(*players[i])>getScore(*players[i+1])) {

		}
	}
}

void toLower(string s) {
	for(int i = 0; i<s.length(); i++) {
		s[i]=tolower(s[i]);
	}
}
