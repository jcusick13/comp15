/*
 * main3.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: JonathanCusick
 */

#include <iostream>
#include "sort3.h"


using namespace std;

int main()
{
        InsertionSort sorter;

        sorter.readList();

        sorter.sort();

        cout << "Output:\n";
        sorter.printArray();

        return 0;
}


