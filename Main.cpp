#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h> //rand and srand
#include<time.h> //time

//yes I know the spelling of "Straight" is incorrect
enum score {NOTHING = 0, PAIR, DOUBLE, TRIPLE, STRAIT, FLUSH, FULLHOUSE = 6, FOURKIND = 7, STRAITFLUSH = 8, ROYAL = 9};
enum suit{HEART, DIAMOND, CLUBS, SPADES};

using namespace std;

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

	string name;
	int valueScore = 0;
	int PopCardValue = 0;

	Hand(string n) {
		for(int i = 0; i<5; i++) {
			hand.insert(hand.begin(), cards[0]);
			cards.erase(cards.begin());
			name = n;
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
	for(int i = 0; i<5; i++) {
		if(h.hand[i]->value>HighCard) {
			HighCard = h.hand[i]->value;
		}
	}
	return HighCard;
}

int getHighCardLoc(Hand h) {
	int HighCardLoc = 0;
	for(int i = 0; i<5; i++) {
		if(h.hand[i]->value>h.hand[HighCardLoc]->value)
				HighCardLoc = i;
		else if(h.hand[i]->value==h.hand[HighCardLoc]->value&&h.hand[i]->suit>h.hand[HighCardLoc]->suit)
			HighCardLoc=i;
	}
	return HighCardLoc;
}

void printCard(int v, int s) {
			//cout<<h.hand[i]->value<<" of "<<h.hand[i]->suit<<endl;
		if(v==11)
			cout<<"Jack";
		else if(v==12)
			cout<<"Queen";
		else if(v==13)
			cout<<"King";
		else if(v==14)
			cout<<"Ace";
		else if(v==2)
			cout<<"Two";
		else if(v==3)
			cout<<"Three";
		else if(v==4)
			cout<<"Four";
		else if(v==5)
			cout<<"Five";
		else if(v==6)
			cout<<"Six";
		else if(v==7)
			cout<<"Seven";
		else if(v==8)
			cout<<"Eight";
		else if(v==9)
			cout<<"Nine";
		else
			cout<<"Ten";

		cout<<" of ";

		if(s==HEART)
			cout<<"Hearts";
		else if(s==DIAMOND)
			cout<<"Diamonds";
		else if(s==CLUBS)
			cout<<"Clubs";
		else if(s==SPADES)
			cout<<"Spades";

		cout<<endl;
}


int PopCardVal = 0;

int getScore(Hand h) {
	int score=9;
	int checker = 0;
	int checker2 = 0;
	int i = 0;
	bool isBreak = false;
	while(isBreak == false) {
		if(score==9) { //royal flush, straitflush, flush and strait
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
					score=STRAITFLUSH;
				else if(checker2!=5) //if all card's suits aren't the same, but is a sequence
					score=STRAIT;
				else
					score=ROYAL;
				isBreak=true;
			}
			else if(checker2==5) { //if all the cards suits are the same, but is not a sequence
				score=FLUSH;
			}
			else {
				score=7;
				i=0;
			}
		}
		else if(score==7) { //four of a kind, three of a kind, full house, pair and two pair
			checker=0;
			i=0;
			while(i<4 && h.hand[i]->value==h.hand[i+1]->value) {
				checker++;
				i++;
			}
			if(checker==3) {
				if(h.hand[0]->value==h.hand[3]->value||h.hand[1]->value==h.hand[4]->value) {
					score=FOURKIND;
					if(h.hand[0]->value==h.hand[1]->value)
						PopCardVal = h.hand[0]->value;
					else
						PopCardVal = h.hand[2]->value;
				}
				else {
					score=FULLHOUSE;
					for(int i = 0; i<3; i++) {
						for(int j = i+1; j<4; j++) {
							for(int k = j+1; k<5; k++) {
								if(h.hand[i]->value==h.hand[j]->value && h.hand[j]->value == h.hand[k]->value) {
									PopCardVal = h.hand[i]->value;
								}
							}
						}
					}
				}
			}
			else if(checker==2) {
				if(h.hand[0]->value==h.hand[2]->value||h.hand[1]->value==h.hand[3]->value||h.hand[2]->value==h.hand[4]->value) {
					score=TRIPLE;
					for(int i = 0; i<3; i++) {
						for(int j = i+1; j<4; j++) {
							for(int k = j+1; k<5; k++) {
								if(h.hand[i]->value==h.hand[j]->value && h.hand[j]->value == h.hand[k]->value) {
									PopCardVal = h.hand[i]->value;
								}
							}
						}
					}
				}
				else {
					score=DOUBLE;
					for(int i = 0; i<4; i++) {
						for(int j = i+1; j<5; j++) {
							if(h.hand[i]->value==h.hand[j]->value&&PopCardVal<h.hand[i]->value)
								PopCardVal = h.hand[i]->value;
						}
					}
				}
			}
			else if(checker==1) {
				score=PAIR;
				for(int i = 0; i<4; i++) {
					for(int j = i+1; j<5; j++) {
						if(h.hand[i]->value==h.hand[j]->value)
							PopCardVal = h.hand[i]->value;
					}
				}
			}
			else {
				score=NOTHING;
				//isBreak = true; //delete later
			}
			isBreak = true;
		}
	}
	return score;
}

//prints hand h to console
void printHand(Hand h) {
	int v = 0;
	int s = 0;
	for(int i = 0; i<5; i++ ){
		v = h.hand[i]->value;
		s = h.hand[i]->suit;
		printCard(v, s);

	}

	cout<<endl<<"-x-"<<endl<<endl;
}

string printScore(int score) {
	if(score==NOTHING)
		return "Nothing";
	else if(score==PAIR)
		return "Pair";
	else if(score==DOUBLE)
		return "Double";
	else if(score==TRIPLE)
		return "Triple";
	else if(score==STRAIT)
		return "Straight";
	else if(score==FLUSH)
		return "Flush";
	else if(score==FULLHOUSE)
		return "Full House";
	else if(score==FOURKIND)
		return "Four of a Kind";
	else if(score==STRAITFLUSH)
		return "Straight Flush";
	else if(score==ROYAL)
		return "Royal Flush";
	else
		return "ERROR: Could not compute";
}

void startGame() {
	Deck d;
	d.shuffle();
	//d.printDeck();

	int playNum; //number of players
	bool cont = true; //true if player wants to continue
	int highCardLoc = 0;

	int cardVal = 0;
	int cardSuit = 0;

	int valueScore = 0;
	string name;

	string input;
	//Hand a;

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
		vector<int> rank; //the number of the player
		cout<<"How many players?"<<endl;
		cin>>playNum;
		for(int i = 0; i<playNum; i++) {
			cout<<"What is thou name?"<<endl;
			cin>>name;
			cout<<endl;
			players.push_back(new Hand(name));
			cout<<players[i]->name<<"'s Hand: "<<endl;
			players[i]->sortHandValue();
			players[i]->sortHandValue();
			printHand(*players[i]);
			players[i]->valueScore = getScore(*players[i]);
			cout<<"Score: "<<players[i]->valueScore<<endl;
			highCardLoc = getHighCardLoc(*players[i]);
			cardVal = players[i]->hand[highCardLoc]->value;
			cardSuit = players[i]->hand[highCardLoc]->suit;
			cout<<"High Card: "<<endl;
			printCard(cardVal, cardSuit); //finish
			players[i]->PopCardValue=PopCardVal;
			if(players[i]->PopCardValue!=0)
				cout<<"Card Value: "<<players[i]->PopCardValue<<endl;
			cout<<endl;
		}
		rankPlayers();
	}while(cont == true);
	cout<<"See You Later :)"<<endl;
}

void rankPlayers() {
	vector<int> rank;
	//adding the players' ranks to a vector
	for(int i = 0; i<players.size(); i++) {
		rank.push_back (players[i]->valueScore);
	}
	//sorting the ranks from lowest to highest
	for(int i = 0; i<rank.size()-1; i++) {
		for(int j = i+1; j<rank.size(); j++) {
			if(rank[i]>rank[j]) {
				rank.insert(rank.begin()+j+1, rank[i]);
				rank.erase(rank.begin()+i);
				if(i>0)
					i--;
			}
			else if(rank[i]==rank[j]) {
				if(players[i]->PopCardValue>players[j]->PopCardValue) {
					rank.insert(rank.begin()+j+1, rank[i]);
					rank.erase(rank.begin()+1);
					if(i>0)
						i--;
				}
			}
			else {
				cout<<"Skipped Rank"<<endl; //delete later
			}
		}
	}
	for(int i = 0; i<rank.size(); i++) {
		cout<<i<<": "<<players[rank[i]]->name<<endl;
	}

}

void toLower(string s) {
	for(int i = 0; i<s.length(); i++) {
		s[i]=tolower(s[i]);
	}
}
