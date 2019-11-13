/*
 * main2.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: JonathanCusick
 */

#include <iostream>
#include "sort2.h"


using namespace std;

int main()
{
        QuickSort sorter;

        arrayWithLength arr = sorter.readList();

        sorter.sort(arr, 0, arr.length-1);

        cout << "Output:\n";
        sorter.printArray();

        return 0;
}


