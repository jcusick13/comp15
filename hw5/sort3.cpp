/*
 * sort3.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: JonathanCusick
 */

#include "sort3.h"

using namespace std;

InsertionSort::InsertionSort(){
	/* Constructor */
	sortArray.length = 0;
	sortArray.arr = NULL;

}

InsertionSort::~InsertionSort(){
	/* Destructor */
	delete []sortArray.arr;
}

void InsertionSort::readList(){
	/* Reads in a list of integers from stdin
	 * into an arrayWithLength
	 */

        int currentCapacity = 10;
        sortArray.arr = new int[currentCapacity];

        while (cin >> sortArray.arr[sortArray.length]) {
                ++sortArray.length;
                if (sortArray.length==currentCapacity) {
                        int *temp = new int[currentCapacity*2];
                        for (int i=0;i<currentCapacity;i++) {
                                temp[i] = sortArray.arr[i];
                        }
                        delete [] sortArray.arr;
                        sortArray.arr = temp;
                        currentCapacity *= 2;
                }
        }
}

void InsertionSort::sort(){
	/* In place insertion sort of sortArray */

	//puts each number in array through algorithm
	for(int i=1; i<sortArray.length; i++){

		//moves element left until it's correct spot
		for(int j=i-1; j>=0; j--){
			//checks if element is in correct place
			if(sortArray.arr[i] < sortArray.arr[j]){
				//moves current element left
				int temp = sortArray.arr[j];
				sortArray.arr[j] = sortArray.arr[i];
				sortArray.arr[i] = temp;

				//resets current location
				i--;
			}
			//stops when element is in correct place
			else{
				break;
			}
		}
	}
}

void InsertionSort::printArray(){
        /* Prints out the elements of sortArray */
	for(int i=0; i<sortArray.length; i++){
		cout<< sortArray.arr[i] << endl;
	}
}
