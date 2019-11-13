/*
 *  sort2.h
 *
 *  Created on: Nov 11, 2014
 *      Author: JonathanCusick
 */

#ifndef SORT2_H_
#define SORT2_H_

#include <iostream>



struct arrayWithLength{
        int length;
        int *arr;
};

class QuickSort {
public:
        // constructor
	QuickSort();

	// destructor
	~QuickSort();

        // read in a list of values from stdin
        arrayWithLength readList();

        // sort function
        void sort(arrayWithLength arr, int left, int right);

        // print the array
        void printArray();

private:
        arrayWithLength sortArray;
};


#endif /* SORT2_H_ */
