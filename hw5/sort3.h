/*
 * sort3.h
 *
 *  Created on: Nov 13, 2014
 *      Author: JonathanCusick
 */

#ifndef SORT3_H_
#define SORT3_H_

#include <iostream>


struct arrayWithLength{
        int length;
        int *arr;
};

class InsertionSort {
public:
        // constructor
	InsertionSort();

	// destructor
	~InsertionSort();

        // read in a list of values from stdin
        void readList();

        // sort function
        void sort();

        // print the array
        void printArray();

private:
        arrayWithLength sortArray;
};

#endif /* SORT3_H_ */
