#include "List_dynamic_array.h"

#include <iostream>
#include <cassert>

using namespace std;

List_dynamic_array::List_dynamic_array()
{
        // TODO: Student writes code here
	// create list
	hand_capacity = INITIAL_CAPACITY;
	cards = new Card[hand_capacity];
	cards_held = 0;
}

List_dynamic_array::~List_dynamic_array()
{
        // TODO: Student writes code here
	// delete list
	delete [] cards;
}

// copy constructor
List_dynamic_array::List_dynamic_array(const List_dynamic_array& source) {
	// explicit copy constructor necessary because of cards array
	cards_held = source.cards_held;
	hand_capacity = source.hand_capacity;

	cards = new Card[hand_capacity];
	for (int i=0;i<cards_held;i++) {
		cards[i] = source.cards[i];
	}
}

// operator= overload
List_dynamic_array List_dynamic_array::operator =(const List_dynamic_array&
		source) {
	// explicit operator= overload necessary because of cards array
	Card *new_cards;

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}

	hand_capacity = source.hand_capacity;
	cards_held = source.cards_held;
	new_cards = new Card[hand_capacity];
	for (int i=0;i<hand_capacity;i++) {
		new_cards[i]=source.cards[i];
	}
	delete [ ] cards;
	cards = new_cards;
	return *this;
}

void List_dynamic_array::print_list()
{
	for(int i=0; i<cards_held; i++) {
		cards[i].print_card();
		if (i != cards_held-1) {
			cout << ",";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::print_list_int()
{
	for(int i=0; i<cards_held; i++) {
		cards[i].print_card_int();
		if (i != cards_held-1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::insert_at_head(Card c)
{
        // TODO: Student writes code here
	// check if we need to expand, and expand if necessary
	if (cards_held+1 >= hand_capacity){
		Card *temp = new Card[hand_capacity *2];
		for(int i=0; i<cards_held; i++){
			temp[i] = cards[i];
		}
		delete [] cards;
		cards = temp;
		hand_capacity *= 2;
	}


	// move all items over one, starting from the last one
	for(int i=cards_held-1; i>=0; i--){
		cards[i+1] = cards[i];
	}

	// insert the new card
	cards[0] = c;
	// update cards_held
	cards_held += 1;
}

void List_dynamic_array::insert_at_tail(Card c)
{
        // TODO: Student writes code here
	// check if we need to expand, and expand if necessary
	if (cards_held+1 >= hand_capacity){
		Card *temp = new Card[hand_capacity *2];
		for(int i=0; i<cards_held; i++){
			*(temp+i) = *(cards+i);
		}
		delete [] cards;
		cards = temp;
		hand_capacity *=2;
	}

	// insert the new card at the end
	cards[cards_held] = c;

	// update cards_held
	cards_held += 1;
}

void List_dynamic_array::insert_at_index(Card c,int index)
{
	// if index is greater than cards_held, then fail
	assert(index <= cards_held);
	
	// TODO: Student writes code here
	// check if we need to expand, and expand if necessary
	if(cards_held+1 >= hand_capacity){
		Card *temp = new Card[hand_capacity*2];
		for(int i=0; i<cards_held; i++){
			temp[i] = cards[i];
		}
		delete [] cards;
		cards = temp;
		hand_capacity *=2;
	}
	
	// move all elements past the insertion point up one
	for(int i=cards_held-1; i>=index; i--){
		cards[i+1] = cards[i];
	}
	
	// insert the card
	cards[index] = c;
	
	// update cards_held
	cards_held +=1;
}

void List_dynamic_array::replace_at_index(Card c, int index) {
	// if index is greater than cards_held-1, then fail
	assert(index < cards_held);

	// TODO: Student writes code here
	// replace the card at index with c
	cards[index] = c;
}

Card List_dynamic_array::card_at(int index)
{
	// if index is out of bounds, fail
	assert (index >= 0 && index < cards_held);
	
	// return the card at index
	// TODO: Student writes code here
	return cards[index];

}

bool List_dynamic_array::has_card(Card c) {
        // TODO: Student writes code here
        // loop through the cards and use the same_card()
        // method in Card.cpp to compare the cards
        // Returns true if the card is in the hand, false otherwise
	for(int i=0; i<cards_held; i++){
		if(cards[i].same_card(c)){
			return true;
		}
	}
	return false;
}

bool List_dynamic_array::remove(Card c)
{
        // TODO: Student writes code here
	// find the card and remove from the hand
	// Returns true if the card was found and removed,
	// false otherwise
	for(int i=0; i<cards_held; i++){
		if(cards[i].same_card(c)){
			for(int j=i; j<cards_held-1; j++){
				cards[j]= cards[j+1];
			}
			cards_held -= 1;
			return true;
		}
	}
	return false;
}

Card List_dynamic_array::remove_from_head()
{
	// if the list is empty, fail
	assert(cards_held > 0);

        // TODO: Student writes code here
        // remove the card at the head, and move all the other
        // cards back one spot
        // Returns the card that was removed
	Card test = cards[0];
	//test.print_card();

	for(int i=1; i<cards_held; i++){
		cards[i-1] = cards[i];
	}
	cards_held -= 1;
	return test;
}

Card List_dynamic_array::remove_from_tail()
{
	// if the list is empty, fail
	assert(cards_held > 0);

        // TODO: Student writes code here
	// removes the card that is at the tail, and returns it
	Card last = cards[cards_held-1];
	cards_held -= 1;
	return last;

}

Card List_dynamic_array::remove_from_index(int index)
{
	// if the list is empty, fail
	assert(cards_held > 0);
	
	// if loc is outside of bounds, fail
	assert(index >= 0 && index < cards_held);

        // TODO: Student writes code here
	// similar to remove_from_head(), but
	// we remove the card at index

	// Returns the card that was removed
	Card temp = cards[index];
	
	if(index == cards_held-1){
		cards_held -=1;
	}
	else{
		for(int i=index; i<cards_held; i++){
			cards[i] = cards[i+1];
		}
		cards_held -= 1;
	}
	return temp;
}

void List_dynamic_array::expand()
{
        // TODO: Student writes code here
	// five steps
	// 1. create new list with twice the capacity
	Card *temp = new Card[hand_capacity*2];

	// 2. copy all cards to the new list
	for(int i=0; i<cards_held; i++){
		temp[i] = cards[i];
	}

	// 3. delete the old list
	delete [] cards;

	// 4. set cards variable to point to the new list
	cards = temp;

	// 5. update hand_capacity
	hand_capacity *=2;
}
