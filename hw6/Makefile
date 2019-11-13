#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -Wall -g3

songsearch: hashfunc.h hashfunc.cpp HashTable.h HashTable.cpp\
	    wordlist.h wordlist.cpp main.cpp
	${CXX} ${FLAGS} -o songsearch hashfunc.cpp HashTable.cpp\
			   wordlist.cpp main.cpp
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw6_design songsearch_design.txt

provide:
	provide comp15 hw6 hashfunc.h hashfunc.cpp HashTable.h HashTable.cpp\
			   wordlist.h wordlist.cpp main.cpp\
			   ReadMe.md Makefile

