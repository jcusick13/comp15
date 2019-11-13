#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include<vector>
#include<string>

using namespace std;

#define MAX_LOAD_FACTOR 0.7
#define INIT_CAPACITY 5

struct LyricInfo{
	int lyric_count;
	int song_index;
};

struct HashedSongs{
	string alpha_only_word;
	vector<LyricInfo> *songs;
};

class HashTable{
public:
	HashTable();
	~HashTable();

	// inserts into the hash table
	void insert(string word, vector<LyricInfo> *songs);

	// finds and returns pointer to LyricInfo vector
	vector<LyricInfo>* find(string word);

	// returns float of the current load factor
	float load_factor() { return (float)table_count /
					table_capacity; }

private:
	HashedSongs *table;
	void expand();
	int table_capacity;
	int table_count;
};

#endif /* HASHTABLE_H_ */
