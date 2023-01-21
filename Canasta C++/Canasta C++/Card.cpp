#include "Card.h"

/* *********************************************************************
Function Name: Card
Purpose: Default constructor for the Card class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Card::Card() : face(0), suit(0), pointVal(0) {

	this->strRep = "NULL";
	this->hasBeenTransferred = false;

}

/* *********************************************************************
Function Name: ~Card
Purpose: Default destructor for the Card class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Card::~Card() {

	face = '0';
	suit = '0';
	strRep = "";
	pointVal = 0;
	hasBeenTransferred = false;

}

/* *********************************************************************
Function Name: Card
Purpose: Default constructor for the Card class.
Parameters:
			suit -> int that represents suit of the card
			face -> int that represents face of the card

Return Value: None
Algorithm:
			1. Call translateSymbols, that will turn the face and suit ints into chars.
			2. Call createPointVal, that will make calculations for the point values of the cards.
Assistance Received: None
********************************************************************* */
Card::Card(int suit, int face) {

	translateSymbols(face, suit);
	createPointVal(this->face, this->suit);
	this->hasBeenTransferred = false;

}

/* *********************************************************************
Function Name: Card
Purpose: Default constructor for the Card class.
Parameters:
			suit -> int that represents suit of the card
			face -> int that represents face of the card
			strRep -> string representation of the card that is passed by value
			pointVal -> int that represents the point value of the card

Return Value: None
Assistance Received: None
********************************************************************* */
Card::Card(char face, char suit, std::string strRep, int pointVal) : face(face), suit(suit), pointVal(pointVal) {

	this->strRep = strRep;
	this->hasBeenTransferred = false;

}

/* *********************************************************************
Function Name: Card
Purpose: Default constructor for the Card class.
Parameters:
			strRep -> string representation of the card that is passed by value

Return Value: None
Algorithm:
			1. Using the this pointer, set the values of the private variables to each character of the input string.
			2. Call createPointVal, that will make calculations for the point values of the cards.
Assistance Received: None
********************************************************************* */
Card::Card(std::string strRep) {

	this->strRep = strRep;
	this->face = strRep.at(0);
	this->suit = strRep.at(1);
	this->hasBeenTransferred = false;
	createPointVal(face, suit);

}

/* *********************************************************************
Function Name: Card
Purpose: Default constructor for the Card class.
Parameters:
			anotherCard -> a const of the Card class that represents another singular card in the deck

Return Value: None
Algorithm:
			1. Set the private variables to their respective getter functions by using the anotherCard object.

Assistance Received: None
********************************************************************* */
Card::Card(const Card& anotherCard) {

	pointVal = anotherCard.getPointVal();
	face = anotherCard.getFace();
	suit = anotherCard.getSuit();
	strRep = anotherCard.getCardStr();
	this->hasBeenTransferred = anotherCard.getTransfer();

}

/* *********************************************************************
Function Name: operator=
Purpose: Move assignment operator for the Card class.
Parameters:
			anotherCard -> a const of the Card class that represents another singular card in the deck

Return Value: *this -> a reference to the object that the operator was called on
Algorithm:
			1. Assign the private values to the anotherCard object.

Assistance Received: None
********************************************************************* */
Card Card::operator=(const Card& anotherCard) {

	this->face = anotherCard.face;
	this->suit = anotherCard.suit;
	this->pointVal = anotherCard.pointVal;
	this->strRep = anotherCard.strRep;
	this->hasBeenTransferred = anotherCard.hasBeenTransferred;
	return *this;

}

/* *********************************************************************
Function Name: Card
Purpose: Default constructor for the Card class.
Parameters:
			anotherCard -> a const of the Card class that represents another singular card in the deck

Return Value: None
Algorithm:
			1. Assign the private values to the anotherCard object.
			2. Create new default values for each private variable.

Assistance Received: None
********************************************************************* */
Card::Card(Card&& anotherCard) noexcept {

	this->face = anotherCard.face;
	this->suit = anotherCard.suit;
	this->pointVal = anotherCard.pointVal;
	this->strRep = anotherCard.strRep;
	this->hasBeenTransferred = anotherCard.hasBeenTransferred;
	anotherCard.face = '0';
	anotherCard.suit = '0';
	anotherCard.strRep = "";
	anotherCard.pointVal = 0;
	anotherCard.hasBeenTransferred = false;

}

/* *********************************************************************
Function Name: Card
Purpose: Move assignment operator for the Card class.
Parameters:
			anotherCard -> a const of the Card class that represents another singular card in the deck

Return Value: *this -> a reference to the object that the operator was called on
Algorithm:
			1. Assign the private values to the anotherCard object.
			2. Check if the address of anotherCard is equal to the address of the object that the operator was called on.
			3. If not, it is safe to reset the values of anotherCard to their default values to avoid self-destructing from happening.
			4. If it is, the values should not be reset.

Assistance Received: None
********************************************************************* */
Card Card::operator=(Card&& anotherCard) noexcept {


	this->face = anotherCard.face;
	this->suit = anotherCard.suit;
	this->pointVal = anotherCard.pointVal;
	this->strRep = anotherCard.strRep;
	this->hasBeenTransferred = anotherCard.hasBeenTransferred;

	//To avoid self destruct
	if (&anotherCard != this) {

		anotherCard.face = '0';
		anotherCard.suit = '0';
		anotherCard.strRep = "";
		anotherCard.pointVal = 0;
		anotherCard.hasBeenTransferred = false;

	}

	return *this;

}

/* *********************************************************************
Function Name: getSuit()
Purpose: Selector for the suit variable.
Parameters: None
Return Value: suit -> char that represents the suit of the card
Assistance Received: None
********************************************************************* */
char Card::getSuit() const {

	return suit;

}

/* *********************************************************************
Function Name: getFace()
Purpose: Selector for the face variable.
Parameters: None
Return Value: face -> char that represents the face of the card
Assistance Received: None
********************************************************************* */
char Card::getFace() const {

	return face;

}

/* *********************************************************************
Function Name: getCardStr()
Purpose: Selector for the strRep variable.
Parameters: None
Return Value: string_representation -> string that represents both the face and the suit 
Assistance Received: None
********************************************************************* */
std::string Card::getCardStr() const {

	return strRep;

}

/* *********************************************************************
Function Name: getPointVal()
Purpose: Selector for the pointVal variable.
Parameters: None
Return Value: pointVal -> int that represents the card itself
Assistance Received: None
********************************************************************* */
int Card::getPointVal() const {

	return pointVal;

}

/* *********************************************************************
Function Name: getTransfer()
Purpose: Selector for the hasBeenTransferred variable.
Parameters: None
Return Value: hasBeenTransferred -> bool that represents if a card has been transferred or not
Assistance Received: None
********************************************************************* */
bool Card::getTransfer() const {

	return hasBeenTransferred;

}

/* *********************************************************************
Function Name: getNumVal()
Purpose: Determines the numerical value of a card based on its face value.
Parameters: None
Return Value: None
Algorithm: 
			1. Use a offset of 48 to properly convert an int to a char.
			2. Enter a switch statement, where it will return a different int value depending on the face value.
			3. If none of the above cases match, return -1.
Assistance Received: None
********************************************************************* */
int Card::getNumVal() const {

	int numOffset = 48;

	switch (face) {
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return (int)face - numOffset;
		break;

	case 'X':
		return 10;
		break;

	case 'A':
		return 11;
		break;

	case 'J':
		return ((isdigit(suit)) ? 15 : 12);
		break;

	case 'Q':
		return 13;
		break;

	case 'K':
		return 14;
		break;

	default:
		return -1;
		break;

	 }

}

/* *********************************************************************
Function Name: setTransfer
Purpose: Mutator function for the Card class.
Parameters: hasBeenTransferred -> bool that represents if a card has been transferred or not
Return Value: None
Assistance Received: None
********************************************************************* */
void Card::setTransfer(bool hasBeenTransferred) {

	this->hasBeenTransferred = hasBeenTransferred;

}

/* *********************************************************************
Function Name: isWild()
Purpose: Will return if the current card is wild or not.
Parameters: None
Return Value: bool for if the current card is wild or not
Assistance Received: None
********************************************************************* */
bool Card::isWild() const {

	//Note: Jokers will be listed as J1 and J2
	if (face == '2' || isdigit(suit))
		return true;
	else
		return false;

}

/* *********************************************************************
Function Name: isSpecial()
Purpose: Will return if the current card is special or not.
Parameters: None
Return Value: bool for if the current card is special or not
Assistance Received: None
********************************************************************* */
bool Card::isSpecial() const {

	if (face == '3')
		return true;
	else
		return false;

}

/* *********************************************************************
Function Name: isNatural()
Purpose: Will return if the current card is natural or not.
Parameters: None
Return Value: bool for if the current card is natural or not
Assistance Received: None
********************************************************************* */
bool Card::isNatural() const {

	return(!(isSpecial() && isWild()));

}

/* *********************************************************************
Function Name: isRedThrees()
Purpose: Will return if there is a red three in the deck.
Parameters: None
Return Value: bool for if there is a red three in the deck
Assistance Received: None
********************************************************************* */
bool Card::isRedThrees() const {

	if (strRep == "3H" || strRep == "3D")
		return true;
	else
		return false;

}

/* *********************************************************************
Function Name: isJoker()
Purpose: Checks to see if a card is a Joker.
Parameters: None
Return Value: bool that determines whather a card is a Joker based on the suit's value
Assistance Received: None
********************************************************************* */
bool Card::isJoker() const {

	return isdigit(suit);

}

/* *********************************************************************
Function Name: translateSymbols
Purpose: Translates ints representing the face and suit into chars and then makes strings
using those two chars. 
Parameters: 
				suit -> int that represents the suit of the card
				face -> int that represents the face of the card
Return Value: void
Algorithm:
				1. Switch the values based on the suit. Based on the number, assign a char value.
				2. If face is under 10, type cast the number plus the offset by static casting.
				3. If face is greater than or equal to 10, switch face depending on value and assign accordingly.
				4. Using strRep, append the two chars.
Assistance Received: None
********************************************************************* */
void Card::translateSymbols(int face, int suit) {

	//Using an offset to convert int to char
	int numOffset = 48;

	switch (suit) {

	case 0:
		this->suit = 'H';
		break;

	case 1:
		this->suit = 'D';
		break;

	case 2:
		this->suit = 'C';
		break;

	case 3:
		this->suit = 'S';
		break;

	}

	if (face < 10) {

		//Using a static cast to not lose data
		this->face = static_cast<char> (face + numOffset);

	}

	else {

		switch (face) {
		case 10:
			this->face = 'X';
			break;

		case 11:
			this->face = 'A';
			break;

		case 12:
			//For Jacks
			this->face = 'J';
			break;

		case 13:
			this->face = 'Q';
			break;

		case 14:
			this->face = 'K';
			break;

		}

	}
	

	this->strRep.push_back(this->face);
	this->strRep.push_back(this->suit);
	 
}

/* *********************************************************************
Function Name: createPointVal
Purpose: Make calculations of the point values of each card.
Parameters:
				face-> char that represents the face of the card
				suit-> char that represents the suit of the card
Return Value: void
Algorithm:
				1. Make a switch statement depending on face. If it is a three, separate the case using if/else statement.
				2. Within individual cases, assign point value.
Assistance Received: None
********************************************************************* */
void Card::createPointVal(char face, char suit) {

	switch (face) {

	case 'A':
	case '2':
		this->pointVal = 20;
		break;

	case '3':
		//Checking if card is a red 3
		//Else it will be assigned the value of a black 3
		if (suit == 'D' || suit == 'H')
			this->pointVal = 100;

		else
			this->pointVal = 5;

		break;

	case '4':
	case '5':
	case '6':
	case '7':
		this->pointVal = 5;
		break;

	case '8':
	case '9':
	case 'X':
	case 'J':
	case 'Q':
	case 'K':
		this->pointVal = 10;
		break;

	}

}

/* *********************************************************************
Function Name: operator==
Purpose: Overloads the == operator for Card objects.
Parameters:
			 c1 ->const that represents the first card object
			 c2 ->const that represents the second card object

Return Value: bool that represents if the string representations of the two cards are equal or not
Algorithm:
			1. Compare the two cards by calling getCardStr on each of them and comparing the
			   returned values by using the == operator.
			2. If the string representations of the two cards are equal, return true. Otherwise, return false.
			 
Assistance Received: None
********************************************************************* */
bool operator==(const Card c1, const Card c2) {

	if (c1.getCardStr() == c2.getCardStr())
		return true;
	else
		return false;

}

/* *********************************************************************
Function Name: operator<
Purpose: Overloads the < operator for Card objects.
Parameters:
			c1 ->const that represents the first card object
			c2 ->const that represents the second card object

Return Value: bool that represents the result of comparing c1PointCal and c2PointVal using <
Algorithm:
			1. Compare the values of the point values of c1 and c2.
			2. If the two cards have the same point value, they are compared based on their numerical values.
			3. If the two cards have different point values, they are comapred based on their point values.

Assistance Received: None
********************************************************************* */
bool operator<(const Card c1, const Card c2) {

	int c1Val = c1.getNumVal();
	int c2Val = c2.getNumVal();
	int c1PointVal = c1.getPointVal();
	int c2PointVal = c2.getPointVal();

	if (c1PointVal == c2PointVal) {

		return c1Val < c2Val;

	}

	else {

		return c1PointVal < c2PointVal;

	}


}

/* *********************************************************************
Function Name: operator>
Purpose: Overloads the > operator for Card objects.
Parameters:
			c1 ->const that represents the first card object
			c2 ->const that represents the second card object
				
Return Value: bool that represents the result of comparing c1PointCal and c2PointVal using >
Algorithm:
			1. Compare the values of the point values of c1 and c2.
			2. If the two cards have the same point value, they are compared based on their numerical values.
			3. If the two cards have different point values, they are comapred based on their point values.

Assistance Received: None
********************************************************************* */
bool operator>(const Card c1, const Card c2) {

	int c1Val = c1.getNumVal();
	int c2Val= c2.getNumVal();
	int c1PointVal = c1.getPointVal();
	int c2PointVal = c2.getPointVal();

	if (c1PointVal == c2PointVal) {

		return c1Val > c2Val;

	}

	else {

		return c1PointVal > c2PointVal;

	}

}