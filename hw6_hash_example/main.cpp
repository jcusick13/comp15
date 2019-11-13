/*
 * main.cpp
 *
 */
#include <iostream>
#include <vector>
#include <string>

#include "HashTable.h"
#include "wordlist.h"



using namespace std;

int main(int argc, char *argv[])
{
	string words[14] = {"Hey","Jude","don't","make","it","bad",
				"Take","a","sad","song","and","make",
				"it","better"};
	HashTable hash_table;
	for (int i=0;i<14;i++) {
		vector<LyricInfo> *songs;
		songs = hash_table.find(words[i]);
		if (songs != NULL){
			cout << "'" << words[i] << "' already exists.\n";
		}
		else {
			// create a dummy vector, for now
			vector<LyricInfo> *songInfoVec =
					new vector<LyricInfo>;
			hash_table.insert(words[i],songInfoVec);
			cout << "Inserted '" << words[i] << "'\n";
		}
	}

	return 0;
	/*
	string filename;
	WordList wordlist;

	if (argc == 2) { // if there is a filename on the command line
		wordlist.read_lyrics(argv[1],true);
	}
	else { // use a pre-defined filename
		filename = "rick_db.txt";
		//filename = "lyrics_fulldb.txt";
	        wordlist.read_lyrics(filename.c_str(),true);
	}
        wordlist.search();

        return 0;
        */
}
