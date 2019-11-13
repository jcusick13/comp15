/*
 * QuickSort.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: JonathanCusick
 */

#include "sort2.h"
#include <stdlib.h>



using namespace std;


QuickSort::QuickSort(){
	/* Constructor */
	sortArray.length = 0;
	sortArray.arr = NULL;

}

QuickSort::~QuickSort(){
	/* Destructor */
	delete []sortArray.arr;
}

arrayWithLength QuickSort::readList(){
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
        return sortArray;
}

void QuickSort::sort(arrayWithLength sortArray,int left,int right){
	/* In place quick sort of sortArray */

	//base cases: length of 0 or 1
	if(abs(right-left < 1)){
		return;
	}
	//saves original R/L variables for recursion argument
	int end_right = right;
	int end_left = left;

	//sets pivot index
	int pivot = left + ((right-left)/2);

	//swaps pivot with first element in the array
	int temp = sortArray.arr[pivot];
	sortArray.arr[pivot] = sortArray.arr[left];
	sortArray.arr[left] = temp;
	//resets pivot's location
	pivot = left;


	//moves inward through the list, comparing to pivot
	//breaks if right == left
	while(left != right){

		//moves R marker left until it's value < pivot's
		while(sortArray.arr[right] > sortArray.arr[pivot] ){
			right --;
			if(right == left){
				break;
			}
		}

		//moves L marker right until it's value >= pivot's
		while(sortArray.arr[left] <= sortArray.arr[pivot]){
			if(right == left){
				break;
			}
			left ++;
			if(right == left){
				break;
			}
		}

		//swaps left and right values
		if(right != left){
			temp = sortArray.arr[left];
			sortArray.arr[left] = sortArray.arr[right];
			sortArray.arr[right] = temp;

			//updates pivot location if it was moved
			if(right == pivot){
				pivot = left;
			}
			if(left == pivot){
				pivot = right;
			}
		}
	}

	//swaps pivot where left and right meet
	temp = sortArray.arr[left];
	sortArray.arr[left] = sortArray.arr[pivot];
	sortArray.arr[pivot] = temp;
	pivot = left;

	//repeats algorithm with small array

	if(pivot == end_left){
		//goes left if (pivot at arr[0])
		sort(sortArray, 0, max(0,end_left));
		//goes right if (pivot at arr[0])
		sort(sortArray, end_left+1, end_right);
	}

	else{
		//goes left normal cases
		sort(sortArray, 0, pivot-1);
		//goes right normal cases
		sort(sortArray, pivot, end_right);
	}
}

void QuickSort::printArray(){
        /* Prints out the elements of sortArray */
	for(int i=0; i<sortArray.length; i++){
		cout<< sortArray.arr[i] << endl;
	}
}





