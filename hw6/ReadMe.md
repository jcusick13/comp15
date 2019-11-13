-----------------------=
-- README COMP 15 HW6 --
--    SONG SEARCH     --
--    9 DEC 2014      --
-----------------------=

------------=
-- PURPOSE --
------------=

~ hw6 is designed to take in a text file database of song lyrics and a user search word and efficiently return the top ten instances of songs with that search word.

~ The resulting output will contain every mention of the search word in each of the top ten songs with the greater context of the word in the song as well.


----------=
-- FILES --
----------=

~ hashfunc.h
	Written by Bob Jenkins, it contains function declarations for a hash function designed to take in strings.

~ hashfunc.cpp
	Written by Bob Jenkins, it contains function definitions for a hashing function.

~ HashTable.h
	Contains function declarations for the dynamic array hash table itself and defines the structures HashedSongs, of which the hash table is composed of, and LyricInfo, of which a vector in HashedSongs is composed of.

~ HashTable.cpp
	Contains the function definitions for the hash table, including insert, find, and expand.

~ wordlist.h
	Contains function declarations for reading in the lyrics to a master database as well as the search function which returns printed out results to the console.

~ wordlist.cpp
	Contains the highest level function defintions in terms of actually running the program. All of the prior header and source files culminate in the functions written here.

~ main.cpp
	Contains the specific calls to functions in wordlist.h and executes the program loop on the console that the user will interact with until ending the program via the search term <BREAK>

~ Makefile
	Used for compiling the program.
		
	
------------=
-- COMPILE --
------------=

~ Use the included Makefile to compile hw6.

-------------------=
-- DATA STRUCTURE --
-------------------=

~ This program is built around the speed and constant lookup time of hash tables. Every unique lyric is hashed to a spot in a dynamic array hash table for quick lookup at search time. 

~ At each location containing a song lyric in the hash table, there is also a pointer to a vector of the top ten songs for that lyric. 

~ Finally, the master database of songs is a vector of Song structs. These structs contain basic information about the song including artist, title, a vector of lyrics, and an index location that is also stored in the top ten songs vector in the hash table. This is the link that allows access back and forth between original song lyrics and hashed lyric counts.



--------------=
-- ALGORITHM --
--------------=

~ The program is broken down into three main parts: read in, hash, search/return. To save time, lyrics are hashed at the same time that they are being read into the master database.

~ READ
	- As songs are being read in, a Song struct is created to hold basic information about the song which is added to a master song database.
	- Each song lyric is then added to an original lyrics vector one by one.

~ HASH
	- While songs are being read in, as soon as a lyric is added to the original lyric vector, it is then immediately hashed. It is stripped of capitals/punctuation to conserve space.
	
    - If a word is not yet in the hash table, it is added and a pointer to an empty top ten vector is assigned that location.
	
	- If a word is already in the hash table, the program checks to see if that song is in the top ten vector at that lyric location. If so, it's lyric count is upped, and all ten are resorted.
	
	- If the word is in the hash table, but not the top ten vector, it is added to an 11th position in the vector while that song is still being read in.
	
	- The top ten vector continues to resort every time there is a change, therefore allowing a song in the 11th position to break into the top ten or to simply be forgotten about and overwritten when the new song gets hashed in to that location.
	
	- All collisions are resolved via linear probing and the maximum load factor is set to be 0.5. As soon as the load factor reaches something larger, the hash table expands to twice it's current size.

~ SEARCH
	- Input guesses are stripped of capitals and punctuation and then hashed to see if there is a word there.
	
	- If there is a matching lyric at that location, the program prints out the top ten songs in that location's top ten vector.
	
	- The master database index is taken from the song in the top ten vector, and the program then goes into the master database to retreive artist, title, and context lyrics for printing.
	
---------=
-- HELP --
---------=

~ Thanks to lab TA Alex Goldschmidt for helping me ensure that my top ten songs vector was correctly tied to it's proper location in the hash table.
