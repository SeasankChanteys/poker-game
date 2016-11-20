#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h> //rand and srand
#include<time.h> //time

enum values {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
values val;

//switch(val) {
//	case ACE:
//		cout<<"ACE";
//		break;
//	case TWO:
//		cout<<"TWO";
//		break;
//	case THREE:
//		cout<<"THREE";
//		break;
//	case FOUR:
//		cout<<"FOUR";
//		break;
//	case FIVE:
//		cout<<"FIVE";
//		break;
//	case SIX:
//		cout<<"SIX";
//		break;
//	case SEVEN:
//			cout<<"SEVEN";
//			break;
//	case EIGHT:
//		cout<<"EIGHT";
//		break;
//	case NINE:
//		cout<<"NINE";
//		break;
//	case TEN:
//		cout<<"TEN";
//		break;
//	case JACK:
//		cout<<"JACK";
//		break;
//	case QUEEN:
//		cout<<"QUEEN";
//		break;
//	case KING:
//		cout<<"KING";
//		break;
//}
//enum suits {HEARTS, DIAMONDS, SPADES, CLUBS};

using namespace std;

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
            for(int j=1; j<14; j++) {
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

	Hand() {
		for(int i = 0; i<5; i++) {
			hand.insert(hand.begin(), cards[cards.size()]);
			cards.pop_back();
		}
	}
};

void startGame();
void toLower(string);
void getScore(Hand);
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
	for(int i = 0; i<5; i++) {

	}
}

void getScore(Hand h) {

}

//prints hand h to console
void printHand(Hand h) {
	for(int i = 0; i<5; i++ ){
		cout<<h.hand[i]->value<<" of "<<h.hand[i]->suit<<endl;
	}
}

void startGame() {
	Deck d;
	d.shuffle();
	d.printDeck();

	int playNum; //number of players
	bool cont = true; //true if player wants to continue

	string input;
	Hand a;

	do {
		cout<<"Do you want to play a game?"<<endl;
		cin>>input;
		toLower(input);
		if(input=="yes"||input=="y") {
		}
		else {
			cont = false;
			break;
		}
		cout<<"How many players?"<<endl;
		cin>>playNum;
		for(int i = 0; i<playNum; i++) {
			players.push_back(new Hand());
			cout<<"Player "<<i+1<<": "<<endl;
			printHand(*players[i]);
			cout<<endl;

		}
	}while(cont == true);
}

void toLower(string s) {
	for(int i = 0; i<s.length(); i++) {
		s[i]=tolower(s[i]);
	}
}
