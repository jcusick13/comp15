/*
 * HashTable.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: Chris Gregg
 */

#include <iostream>
#include "HashTable.h"
#include "hashfunc.h"

using namespace std;

HashTable::HashTable(){
	/* Constructor */
	table_capacity = INIT_CAPACITY;
	table_count = 0;
	table = new HashedSongs [table_capacity];

	// initializes each spot to an empty string
	for(int i=0; i<table_capacity; i++){
		table[i].alpha_only_word = "";
	}
}

HashTable::~HashTable(){
	/* Destructor */

	// walks through table and deletes pointers
	// if alpha_only_word != ""
	for(int i=0; i<table_capacity; i++){
		if(table[i].alpha_only_word != ""){
			delete [] table[i].songs;

			table_capacity --;
		}
	}

}

void HashTable::insert(string word, vector<LyricInfo> *songs){
	/* Inserts a word and accompanying vector pointer
	 * into the hash table. Word must already have
	 * alpha_only called -- function expects all words
	 * lower case and stripped of punctuation.
	 */

	// checks load factor for expansion
	if(load_factor() >= MAX_LOAD_FACTOR){
		expand();
	}

	unsigned int hash_value = hash_string(word);
	int table_position;
	bool done_inserting = false;
	int attempt = 0;

	while(!done_inserting){

		// determines table_position
		table_position = (hash_value % table_capacity) + attempt;

		if(table[table_position].alpha_only_word != ""){
			// position occupied - increases attempt
			attempt ++;

		}
		else{
			// found open position
			// places word into alpha_only_word
			table[table_position].alpha_only_word = word;

			// places songs into LyricInfo struct
			LyricInfo *lyric_info = new LyricInfo();
			lyric_info->lyric_count = 1;
			lyric_info->song_index = -1; // ** what to put here?
						     // ** get from Song class

			// places LyricInfo struct into songs vector
			songs->push_back(*lyric_info);

			done_inserting = true;
		}
	}
}

vector<LyricInfo>* HashTable::find(string word){
	/* Searches hash table for a word. If found,
	 * returns a pointer to the vector songs so that
	 * the lyric count can be updated. Else, it returns
	 * a NULL pointer if the word is not in the hash table.
	 */

	// hashes the string to an integer
	unsigned int hash_value = hash_string(word);

	// searches for the entry in the hash table,
	// handles collisions via linear probing
	int attempt = 0;
	bool done_searching = false;
	bool found_word = false;
	int table_position;

	while(!done_searching){
		// determines table position
		table_position = (hash_value % table_capacity) + attempt;

		// checks table positions alpha_only_word
		// finds empty position
		if(table[table_position].alpha_only_word == ""){

			// returns NULL pointer
			found_word = false;
			done_searching = true;
		}

		// table position occupied with incorrect word
		else if(table[table_position].alpha_only_word != word){

			// increases attempt for linear probing to find word
			attempt++;
		}

		// word is found
		else{
			// marks found word to avoid returning NULL pointer
			found_word = true;
			done_searching = true;
		}
	}

	// returns result of find() function
	if(found_word){
		// returns songs pointer
		return table[table_position].songs;
	}
	else{
		// word not found, returns NULL
		return NULL;
	}

}

void HashTable::expand(){
	/* Expands the hash table to twice it's current
	 * size and rehashes all of the keys in the table
	 * before the expand function. Does not make a
	 * "deep copy" of the vector at each key location,
	 * but instead, passes along the pointer to the
	 * new hash table location.
	 */

	// creates a new table with 2x capacity
	HashedSongs *new_table = new HashedSongs [table_capacity * 2];

	// initializes the new table with alpha_only_word set to ""
	for(int i=0; i<table_capacity; i++){
		table[i].alpha_only_word = "";
	}
	// swaps the new and old table pointers,
	HashedSongs *temp;

	temp = table;
	table = new_table;
	new_table = temp;

	// updates table capacity
	table_capacity *= 2;

	// resets table_count to prepare for re-hashing
	table_count = 0;

	// rehashes all old keys (existing alpha_only_words)
	for(int i=0; i<table_capacity; i++){
		if(new_table[i].alpha_only_word != ""){

			// searches for entries in the hash table
			// handles collisions via linear probing
			unsigned int hash_value = hash_string(
					new_table[i].alpha_only_word);
			int table_position;
			bool done_inserting = false;
			int attempt = 0;

			while(!done_inserting){
				// determines table_position
				table_position = (hash_value % table_capacity)
						+ attempt;

				if(table[table_position].alpha_only_word != "")
				{	// position occupied
					// increases attempt
					attempt ++;
				}
				else{
					// found open position
					// places word into alpha_only_word
					table[table_position].alpha_only_word =
						new_table[i].alpha_only_word;

					// places songs into LyricInfo struct
					table[table_position].songs =
							new_table[i].songs;

					done_inserting = true;
				}

			}
		}
	}

	// deletes old table
	delete [] new_table;

}
