/* sandwichList.cpp
 * Comp 15 
 * Spring 2014 
 * Lab 4
 */

#include "sandwichList.h"


SandwichList::SandwichList()
{
	capacity = INITIAL_SIZE;
	orders = new Order[INITIAL_SIZE];
	orderCount = 0;

	back = 0;
	front = 0;
}

bool SandwichList::isEmpty()
{
	if (size() == 0)
		return true;
	else
		return false;
}


int SandwichList::size()
{
        return orderCount;
        // you could use the following arithmetic (but be careful):
	//return (back - front + capacity) % capacity;
}

//function to remove Order from the front of the queue
Order SandwichList::dequeue()
{

// TODO: Students write code here

	//check for existing queue
	if(isEmpty()){
		exit(EXIT_FAILURE);
	}
	//create holder to return order
	Order *temp = new Order;
	*temp = orders[front];

	//if room, just slide front over one
	// update orderCount, return order
	if(front != capacity-1){
		front +=1;
		orderCount -= 1;
		return *temp;
	}
	//front at capacity, wrap around to start of array
	else{
		front = 0;
		orderCount --;
		return *temp;
	}

	//free temp memory
	delete []temp;
}

//add an element, make sure it is not full, if it is call expand function
void SandwichList::enqueue(const Order& sw)
{

// TODO: Students write code here
	
	//if queue is full, expand
	if(back == front){
		expandList();

	}
	//if room, add in back, ++ count
	if(back < capacity-1){
		if(size() == orderCount){
			expandList();
			orders[back] = sw;
			back ++;
			orderCount ++;
		}
		else{
			back = 0;
			orders[back] = sw;
			orderCount += 1;
		}
	}
}

//Double the queue size, copy the values, and reset back and front
void SandwichList::expandList()
{

// TODO: Students write code here

	//allocate new array
	Order *expand = new Order[capacity*2];

	//copy over old
	for(int i=0; i<capacity; i++){
		expand[i] = orders[(front+i)%capacity];
	}
	//free storage
	delete[] orders;

	//repoint to new array
	orders = expand;

	//update capacity
	capacity *=2;

	//reset front & back
	front = 0;
	back = (capacity/2);
}

void SandwichList::printOrder(Order s)
{
	cout << s.sandwich << " " << s.customerName << " " << s.orderNbr << " " << s.fries;
	cout << endl;
}



