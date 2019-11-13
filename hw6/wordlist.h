/*
 * wordlist.h
 *
 *  Created on: Nov 30, 2014
 *      Author: JonathanCusick
 */

#ifndef WORDLIST_H_
#define WORDLIST_H_

#include <string>
#include <sstream>
#include <vector>

#include "HashTable.h"


using namespace std;

struct Song{
	string artist;
	string title;
	int all_songs_index;
	vector<string> orig_lyrics;
};

class WordList{
public:

	WordList();
	~WordList();

	vector<Song> database;
	HashTable hash_table;

	// converts a string to lower case and without punctuation
	string alpha_only(string s);

	// updates the lyric info in a hash location's vector
	void update_lyric_info(vector <LyricInfo> *songs, Song curr_song);

	// reads the lyrics in from a file, adds them to all_songs
	void read_lyrics(const char * filename, bool show_progress);

	// searches stored lyrics, returns top ten songs with that word
	void search(string word);

private:
	void sort(vector <LyricInfo>* songs);
	void print_context(string word, int index, int total);

};

#endif /* WORDLIST_H_ */
