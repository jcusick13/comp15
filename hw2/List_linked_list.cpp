#include "List_linked_list.h"

#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

List_linked_list::List_linked_list(){
	head = NULL;
}

List_linked_list::~List_linked_list()
{
	// delete list by looping through and deleting each node
}

// copy constructor
List_linked_list::List_linked_list(const List_linked_list& source) {
	// explicit copy constructor necessary because of cards array
	if (source.head == NULL) return; // nothing to do

	head = new Card_Node;
	Card_Node *this_current = head;
	Card_Node *source_current = source.head;

	while (source_current != NULL) {
		// deep copy each Card_Node
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next = new_node;
			new_node->card = source_current->next->card;
		}
		else {
			this_current->next = NULL; // at tail
		}
		source_current = source_current->next;
		this_current = this_current->next;
	}
}

// operator= overload
List_linked_list List_linked_list::operator =(const List_linked_list&
		source) {
	// explicit operator= overload necessary because of cards array

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}
	// delete all current cards
	while (head != NULL) {
		Card_Node *next = head->next;
		delete head;
		head = next;
	}
	// copy over all cards from source list
	if (source.head == NULL) return *this; // nothing to do

	head = new Card_Node;
	Card_Node *this_current = head;
	Card_Node *source_current = source.head;

	while (source_current != NULL) {
		// deep copy each Card_Node
		this_current->card = source_current->card;
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next = new_node;
		}
		else {
			this_current->next = NULL; // at tail
		}
		source_current = source_current->next;
		this_current = this_current->next;
	}
	return *this;
}

void List_linked_list::print_list()
{
	Card_Node *current = head;
	while (current != NULL) {
		current->card.print_card();
		if (current->next != NULL) {
			cout << ",";
		}
		else {
			cout << "\n";
		}
		current = current->next;
	}
}

void List_linked_list::print_list_int()
{
	Card_Node *current = head;
	while (current != NULL) {
		current->card.print_card_int();
		if (current->next != NULL) {
			cout << ",";
		}
		else {
			cout << "\n";
		}
		current = current->next;
	}
}

int List_linked_list::cards_in_hand(){
	//create node identifier and variable to keep track of cards
	Card_Node *curr = head;
	int card_count = 1;

	//empty list returns 0
	if(curr == NULL){
		return 0;
	}
	else{//list >0, +1 for each non-NULL
		while(curr->next != NULL){
			curr = curr->next;
			card_count += 1;
		}
		return card_count;
	}
}


void List_linked_list::make_empty(){
	head = NULL;
	head->next = NULL;
}

void List_linked_list::insert_at_head(Card c){
	//create new node to hold input card c
	Card_Node *newNode = new Card_Node();
	newNode->card = c;

	//check for NULL, update two pointers
	if(head == NULL){
		head = newNode;
		newNode->next = NULL;
	}
	else{
		newNode->next = head;
		head = newNode;
	}
}

void List_linked_list::insert_at_tail(Card c){
	//create new node to hold input card c
	Card_Node *newNode = new Card_Node();
	newNode->card = c;

	//create reference pointer to walk through list
	Card_Node *curr = head;

	//check for empty list, if so, set c as only element
	if(curr == NULL){
		head = newNode;
		newNode->next = NULL;
	}
	else{

		//loop through list to find last card
		while(curr->next != NULL){
			curr = curr->next;
		}
		//find end of list
		//update two pointers to add card c
		newNode->next = NULL;
		curr->next = newNode;
	}
}

void List_linked_list::insert_at_index(Card c, int index){
	//create new node to hold input card c
	Card_Node *newNode = new Card_Node();
	newNode->card = c;

	//create reference pointer and index counter
	Card_Node *curr = head;
	int place = 1;

	if(index == 0){
		//if list empty, make card c head node
		if(head == NULL){
			head = newNode;
			newNode->next = NULL;
		}
		else{//index 0, existing list
			newNode->next = curr;
			head = newNode;
		}
	}
	else{
		//fail if index is negative
		if(index < 0){
			exit(EXIT_FAILURE);
		}
		//not empty - loop through, find correct index
		while(place != index){
			if(curr->next != NULL){
				curr = curr->next;
				place +=1;
			}
		}
		//exit program if improper index given
		if(place > index){
			exit(EXIT_FAILURE);
		}
		//at correct index, insert card c
		//update two pointers
		newNode->next = curr->next;
		curr->next = newNode;
	}
}

void List_linked_list::replace_at_index(Card c, int index){
	//create reference pointer and index counter
	Card_Node *curr = head;
	int place = 1;

	//create new node to hold card c
	Card_Node *newNode = new Card_Node();
	newNode->card = c;

	//if list empty or given negative index, exit
	if(head == NULL || index < 0){
		exit(EXIT_FAILURE);
	}
	//replace at head, update 2 pointers
	if(index == 0){
		newNode->next = head->next;
		head = newNode;
	}
	//handle list length 1
	if(head->next == NULL){
		//index is w/i bounds, update 2 pointers
		if(index == 0){
			newNode->next = NULL;
			head = newNode;
		}
		else{
			//index out of bounds, fail
			exit(EXIT_FAILURE);
		}
	}
	//handle list length 2
	if(index != 0 && head->next->next == NULL){
		//check index w/i list, if no, fail
		if(index > 1){
			exit(EXIT_FAILURE);
		}
		//if index == 1, replace
		if(index == 1){
			newNode->next = head->next->next;
			head->next = newNode;
		}
	}
	//handle list >2
	while(place != index && index != 0){
		if(curr->next->next != NULL){
			curr = curr->next;
			place += 1;
		}
	}
	//at index-1, replace curr-> next with card c
	//update two pointers
	if(index != 0){ //already handled index 0 earlier
		newNode->next = curr->next->next;
		curr->next = newNode;
	}
}



Card List_linked_list::card_at(int index){
	//create reference pointer, holder to return card
	Card_Node *curr = head;
	Card_Node *temp = new Card_Node;


	//check for empty list, if so, exit fn
	if(curr == NULL){
		exit(EXIT_FAILURE);
	}

	//check for list of one
	if(curr->next == NULL){
		if(index == 0){ //return index 0
			temp = head;
		}
		else{ //index out of range
			exit(EXIT_FAILURE);
		}
	}
	//create counter
	//check index == 0
	int count = 0;
	if(index == 0){
		temp = head;
	}
	else{
		//loop through list >1 to find index, break
		while(curr->next != NULL){
			curr = curr->next;
			count += 1;
			if(count == index){
				break;
			}
		}
	}

	//found index, assign to temp for return
	temp = curr;
	return temp->card;
}

bool List_linked_list::has_card(Card c){
	//check for empty list
	if(head == NULL){
		exit(EXIT_FAILURE);
	}
	//make reference pointer
	Card_Node *curr = head;

	//compare head
	if(curr->card.same_card(c)){
		return true;
	}
	//loop through list, compare along way
	else{
		while(curr->next != NULL){
			curr = curr->next;
			if(curr->card.same_card(c)){
				return true;
			}
		}
		return false;
	}
}

bool List_linked_list::remove(Card c){
	//check for empty list
	if(head == NULL){
		return false;
	}
	//make reference pointer
	Card_Node *curr = head;

	//compare head
	if(curr->card.same_card(c)){
		head = curr->next;
		return true;
	}
	//loop through list, compare along way
	else{
		while(curr->next != NULL){
			//if c exists, remove, delete
			if(curr->next->card.same_card(c)){
				curr->next = curr->next->next;
				return true;
			}
			else{ //keep searching for c
				curr = curr->next;
			}
		}
		return false;
	}
}

Card List_linked_list::remove_from_head(){
	//check for empty list
	if(head == NULL){
		exit(EXIT_FAILURE);
	}
	else{
		//remember original head to return
		Card_Node *temp = new Card_Node();
		temp = head;

		//reset head to second card in deck
		head = head->next;
		return temp->card;
	}
}

Card List_linked_list::remove_from_tail(){
	//create reference pointer to loop through list
	Card_Node *curr = new Card_Node();
	curr = head;

	//create reference for last card for return
	Card_Node *temp = new Card_Node();

	//check for empty list, if so, exit fn
	if(curr == NULL){
		exit(EXIT_FAILURE);
	}

	//check for list of one
	//if so, delete list, return head
	if(curr->next == NULL){
		temp = head;
		head = NULL;
		return temp->card;
	}

	//loop through list >1 to find last card
	while(curr->next->next != NULL){
		curr = curr->next;
	}

	//found last card, assign to temp for return
	//remove by changing one pointer
	temp = curr->next;
	curr->next = NULL;
	return temp->card;
}

Card List_linked_list::remove_from_index(int index){
	//create reference pointer and index counter
	Card_Node *curr = head;
	int place = 1;

	//create reference for last card for return
	Card_Node *temp = new Card_Node();

	//if list empty or given negative index, exit
	if(head == NULL || index < 0){
		exit(EXIT_FAILURE);
	}
	//remove at head, update 2 pointers
	if(index == 0){
		temp = curr;
		head = temp->next;
		return temp->card;
		exit(EXIT_SUCCESS);
	}
	//handle list length 1
	if(head->next == NULL){
		//index is w/i bounds, update 2 pointers
		if(index == 0){
			temp = head;
			head = NULL;
			return temp->card;
			exit(EXIT_SUCCESS);
		}
		else{
			//index out of bounds, fail
			exit(EXIT_FAILURE);
		}
	}
	//handle list length 2
	if(head->next->next == NULL){
		//if index == 1, remove
		if(index == 1){
			temp = head->next;
			head->next = NULL;
			return temp->card;
			exit(EXIT_SUCCESS);
		}
		else{
			exit(EXIT_FAILURE);
		}
	}
	//handle list >2
	if(index != 0){
		while(place != index){
			if(curr->next->next != NULL){
				curr = curr->next;
				place += 1;
			}
		}
	}
	//at index-1, replace curr-> next with card c
	//update two pointers
	if(index != 0){ //already handled index 0 earlier
		temp = curr->next;
		curr->next = curr->next->next;
	}
	return temp->card;
}

