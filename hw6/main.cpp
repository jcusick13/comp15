/*
 * main.cpp
 *
 */
#include "wordlist.h"
#include "HashTable.h"

#include <iostream>
#include <vector>
#include <string>


int main(int argc, char *argv[])
{
	string filename;
	WordList wordlist;

	if (argc == 2) {
		// takes file on command line for input
		wordlist.read_lyrics(argv[1],true);
	}
	else{
		// takes predefined file if there is nothing passed in
		filename = "lyrics_fulldb.txt";
	        wordlist.read_lyrics(filename.c_str(),true);
	}

	// sets input to guess word
	string guess;
	cin >> guess;

	// continues program until exit command is entered
	while(guess != "<BREAK>"){
		wordlist.search(guess);
		cin >> guess;
	}

        return 0;
}
