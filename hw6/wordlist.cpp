/*
 * wordlist.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: JonathanCusick
 */

#include "wordlist.h"
#include "HashTable.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

WordList::WordList(){
	/* Constructor */

	vector<Song> database;
	HashTable hash_table;
}

WordList::~WordList(){
	/* Destructor */


}

string WordList::alpha_only(string s){
	/* Converts a strong to lower case and alphabetic
	 * characters only. Example: "Bang!" becomes "bang".
	 *
	 * Takes in a string and returns
	 * a new, alpha-only string, does not modify
	 * original string.
	 */

        ostringstream ss;
        for (size_t i=0;i<s.length();i++) {
                if (isalnum(s[i])){
                        ss << (char)(tolower(s[i]));
                }
        }
        return ss.str();
}

void WordList::update_lyric_info(vector <LyricInfo> *songs, Song curr_song)
{
	/* To be called when a LyricInfo position in
	 * the hash table should be updated. Takes in
	 * a vector at a prespecified location in the
	 * hash table.
	 *
	 * If the song passed in is in the vector, it's
	 * lyric count is increased and the vector is resorted.
	 * Otherwise, it is added to the 11th position in
	 * vector.
	 *
	 * The song's lyric (word) must NOT contain
	 * capitals or punctuation.
	 */

	bool found = false;

	// searches through songs vector for match
	for(int i=0; i<(*songs).size(); i++){
		if((*songs)[i].song_index == curr_song.all_songs_index){
			// LyricInfo location is found, updates lyric_count
			(*songs)[i].lyric_count ++;

			// breaks loop
			found = true;
			break;
		}
	}
	if(!found){
		// doesn't exist yet

		// creates new LyricInfo
		LyricInfo* add = new LyricInfo;
		add->lyric_count = 1;
		add->song_index = curr_song.all_songs_index;

		// inserts no further back than 11th spot
		if((*songs).size() >= 11){
			(*songs)[10] = *add;
		}
		else{
			(*songs).push_back(*add);
		}
	}
	// resorts the vector
	sort(songs);
}

void WordList::read_lyrics(const char * filename, bool show_progress)
{	/* Reads in song data from a disk file.
	 * Takes in the name of the file and a boolean
	 * to ask for progress status.
	 *
	 * Each time a word is found, it is added to two lists--
	 * one vector of original lyrics (containing punctuation, etc)
	 * and a hash table of alpha-only strings.
	 */

	// creates an input stream for progress indicator
        ifstream in(filename);
        int song_count = 0;
	string artist, title, word;


	// while more data to read
	while ( ! in.eof() )
	{
		// takes first line as artist
		getline(in, artist);
		if (in.fail()) break;

		// takes second line as title
		getline(in, title);
		if (in.fail()) break;

		// makes new Song class to store info
		Song song = Song();
		song.artist = artist;
		song.title = title;
		song.all_songs_index = song_count;
		song_count ++;

		// adds Song class to all_songs vector
		database.push_back(song);


		if (show_progress){
			if (song_count % 10000 == 0) { //song_count % 10000 == 0
				cout << "At " << song_count <<
					" Artist: " << artist     <<
					" Title: "   << title << endl;
			}
		}


		// reads in words until end of song
		while ( in >> word && word != "<BREAK>" ){

			// adds word to original lyrics vector
			database[song_count-1].orig_lyrics.push_back(word);

			// -- handles hashing --

			// removes upper case/punctuation from word
			string alpha_word = alpha_only(word);

			// creates temp pointer to pass to find()
			vector<LyricInfo> *temp = new vector<LyricInfo>;
			vector<LyricInfo> *songs;

			// searches hash table
			songs = hash_table.find(alpha_word, temp);

			// deletes temp pointer
			temp->clear();

			if(songs != NULL){
				// word exists in table, update count
				update_lyric_info(songs, song);
			}
			else{
				// word not in table, inserts
				hash_table.insert(alpha_word,
						song.all_songs_index);
			}
		}
		// skips the new line left behind
		in.ignore();
	}
}

void WordList::search(string word){
	/* Takes in any typed word, strips it of
	 * capitals/punctuation and searches
	 * through songs database.
	 *
	 * Returns a descending top-ten string list
	 * of songs by word frequency. Each song
	 * in the list will have every occurrence
	 * of the word printed out within the context
	 * of the preceding and trailing five words.
	 */

	// strips words of capitals/punctuation
	string alpha_word = alpha_only(word);

	// creates temp pointer to pass to find()
	vector<LyricInfo> *temp = new vector<LyricInfo>;
	vector<LyricInfo> *songs;

	// searches hash table
	songs = hash_table.find(alpha_word, temp);

	if(songs != NULL){

		// tracker to ensure max of 10 songs printed
		int ten;

		// sets ten to min(10, songs.size())
		if(10 <= songs->size()){
			ten = 10;
		}
		else{
			ten = songs->size();
		}

		// word exists, prints info on top results
		for(int i=0; i<ten; i++){

			// prints out searched word with context
			print_context(alpha_word, (*songs)[i].song_index,
					(*songs)[i].lyric_count);
		}
	}
	cout << "<END OF REPORT>" << '\n';
}


void WordList::print_context(string word, int index, int total){
	/* Takes in a word and song index for the
	 * location of a song in the master database.
	 *
	 * Returns every occurrence of that word
	 * with five words of context before and
	 * after, along with the artist and title
	 * of the song.
	 */

	int count = 0;
	Song curr = database[index];

	// searches through each word in current song
	for(int i=0; i<curr.orig_lyrics.size(); i++){

		// removes capitals/punctuation
		string alpha = alpha_only(curr.orig_lyrics[i]);

		//compares to input word
		if(alpha == word){
			count ++;

			// prints out song information
			cout << "Title: " << curr.title << endl;
			cout << "Artist: " << curr.artist << endl;
			cout << "Context: ";

			// creates variables to ensure function prints words
			// within bounds of song
			int start;
			int stop;

			// sets start to max(i-5, 0)
			if((i-5) > 0){
				start = i-5;
			}
			else{
				start = 0;
			}

			// sets stop to min(i+6, end of orig_lyrics)
			if(i+6 < curr.orig_lyrics.size()){
				stop = i+6;
			}
			else{
				stop = curr.orig_lyrics.size();
			}

			// prints out each lyric
			for(int j=start; j<stop; j++){
				cout << curr.orig_lyrics[j] << " ";
			}
			cout << "\n" << endl;

			// checks to see if loop can break early
			if(count >= total){
				break;
			}
		}
	}
}

void WordList::sort(vector<LyricInfo>* songs){
	/* Uses a descending in place insertion
	 * sort to keep the top ten vector at
	 * each hash location ordered.
	 */

	// goes through each element in the vector
	for(int i=1; i<songs->size(); i++){

		// moves element left until it's correct spot
		for(int j=i-1; j>=0; j--){
			//checks if element is in correct place
			if((*songs)[i].lyric_count > (*songs)[j].lyric_count){
				//moves current element left

				// sets temp = j
				LyricInfo* temp = new LyricInfo;
				temp->lyric_count = (*songs)[j].lyric_count;
				temp->song_index = (*songs)[j].song_index;

				// sets j = i
				(*songs)[j].lyric_count =
						(*songs)[i].lyric_count;
				(*songs)[j].song_index =
						(*songs)[i].song_index;

				// sets i = temp
				(*songs)[i].lyric_count = temp->lyric_count;
				(*songs)[i].song_index = temp->song_index;

				// resets current location
				i--;
			}
			// stops when element is in correct place
			else{
				break;
			}
		}
	}
}

