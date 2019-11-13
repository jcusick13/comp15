//
//  SelectionSort.cpp
//  Sorts integers using the SelectionSort algorithm


#include "SelectionSort.h"


using namespace std;

SelectionSort::SelectionSort(){
	/* Constructor */
        sortArray.length = 0;
        sortArray.arr = NULL;
}

SelectionSort::~SelectionSort(){
	/* Destructor */
	delete []sortArray.arr;
}

void SelectionSort::readList(){
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

void SelectionSort::sort(){
	/* In place selection sort of sortArray */

	//performs sort algorithm for each array element
	for(int i=0; i<sortArray.length-1; i++){
		//sets to current array location
		int min = i;

		//compares each element to min
		for(int j=i+1; j<sortArray.length; j++){
			//checks if curr element is less than min
			if(sortArray.arr[j] < sortArray.arr[min]){
				//resets min to curr element's location
				min = j;
			}
		}

		//swaps min to front of array if it wasn't there
		if(sortArray.arr[i] != sortArray.arr[min]){
			int temp = sortArray.arr[i];
			sortArray.arr[i] = sortArray.arr[min];
			sortArray.arr[min] = temp;
		}
	}
}

void SelectionSort::printArray(){
        /* Prints out the elements of sortArray */
	for(int i=0; i<sortArray.length; i++){
		cout<< sortArray.arr[i] << endl;
	}
}



