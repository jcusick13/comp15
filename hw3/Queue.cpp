/*
 * Queue.cpp
 *
 */

#include <iostream>
#include <cstdlib>
#include "Queue.h"

// TODO: Student writes this class

Queue::Queue(){
	//define starting parameters
	capacity = QUEUE_INIT_CAPACITY; //starts at 2
	queue_array = new Student[QUEUE_INIT_CAPACITY];
	size = 0;
	front = 0;
	back = 0;
}

Queue::~Queue(){
	// write code here
	delete [] queue_array;
}

void Queue::enqueue(Student c){
	//if full, expand
	if(size == capacity){
		expand();
	}

	//add to queue
	queue_array[back] = c;

	//update size and back
	back = (back + 1) % capacity;
	size ++;
}

Student Queue::dequeue(){

	//grab front student
	Student temp = queue_array[front];

	//move front foward one
	front = (front + 1) % capacity;

	//update size, return front student
	size --;
	return temp;
}

bool Queue::is_empty(){
	if(size <= 0){
		return true;
	}
	else{
		return false;
	}
}

void Queue::expand(){
	//make new array, 2x
	Student *temp = new Student[capacity*2];

	//copy over old array
	for(int i = 0; i<size; i++){
		temp[i] = queue_array[(front + i) % capacity];
	}

	//delete old list
	delete [] queue_array;

	//repoint to new array
	queue_array = temp;

	//reset front, back, capacity
	front = 0;
	back = capacity;
	capacity *= 2;
}
