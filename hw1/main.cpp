#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


#include "hand.h"

#define SEED_RANDOM false


int main() {
	List_dynamic_array da;

	Card c('A','D');

	da.insert_at_index(c,0);

	c.set_suit(HEART);
	c.set_rank(TEN);
	da.insert_at_index(c,0);

	c.set_suit(SPADE);
	c.set_rank(FIVE);
	da.insert_at_index(c,0);

	c.set_suit(CLUB);
	c.set_rank(TWO);
	da.insert_at_index(c,0);

	c.set_rank(NINE);
	da.insert_at_index(c,0);

	c.set_suit(HEART);
	c.set_rank(FOUR);
	da.insert_at_index(c,0);
	da.print_list();

	for (int i=0;i<6;i++) {
		cout << "Removed ";
		da.remove_from_tail().print_card();
		cout << "\n";
		da.print_list();
	}

	return 0;
}



/*int main(int argc, char **argv)
{
	if (SEED_RANDOM) srand(time(NULL));
	Hand deck, hand1, hand2;
	
	deck.create_deck();
	deck.print_hand();

	Card c;
	c.set_suit(HEART);
	c.set_rank(THREE);

	//deck.remove_card(c);

	deck.shuffle();
	deck.print_hand_int();

	for (int i=0;i<5;i++) {
		deck.deal_card_from_top(hand1);
		deck.deal_card_from_top(hand2);
	}
	hand1.order_hand();
	hand2.order_hand();
	deck.print_hand();
	hand1.print_hand();
	hand2.print_hand();
	
	return 0;
}*/

