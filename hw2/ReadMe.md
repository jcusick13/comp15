-----------------------=
-- README COMP 15 HW2 --
--    LINKED LISTS    --
--    26 SEPT 2014    --
-----------------------=

------------=
-- PURPOSE --
------------=

~ hw2 contains functions to model a standard deck of playing cards

~ These functions can be used in an implementation of a card game, or study there of

----------=
-- FILES --
----------=

~ hand.h
	Defines class Hand and it's functions
	Used to hold individual cards and model gameplay

~ hand.cpp
	Function definitions for the hand header file
	Order by suit, shuffle, deal, etc.

~ card.h
	Defines class Card of suit s and rank r
	Used to populate the Hand class

~ card.cpp
	Function definitions for the Card class
	Set card suit, rank, print card, etc

~ List_linked_list.h
	Contains a struct 'Card_Node' and class 'List_linked_list'
	Functions relating to ordering, adding, removing cards, etc.

~ List_linked_list.cpp
	Function definitions for moving cards througout hand

~ main.cpp
	Creates a standard deck of playing cards
	Performs basic operations including shuffle, print hand

------------=
-- COMPILE --
------------=

~ Use include Makefile to compile hw2


-------------------=
-- DATA STRUCTURE --
-------------------=

~ hw2 is written using singuarly linked lists, with each node containing an individual Card

~ all lists include the private variables head and next

~ complied and tested with the clang++ compiler in Eclipse


