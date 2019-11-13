#include "hookbook.h"

HookBook::HookBook()
{
    hbook = new Pirate[INIT_CAPACITY];
    currentCapacity = INIT_CAPACITY;
    pirateCount = 0;
}


    /* Adds a new pirate to HookBook, probably the member should
       be created by the hookbook system, for now it is sent in
       from main, friends is a pointer to a dynamic array we
       copy it to the hookbook data structure, if it is null the pirate
       has no friend*/
    
bool HookBook::addPirate(int member, string memberName)
{
    //check to see if we need to expand to add
    if(pirateCount >= currentCapacity)
    {
            // check to see if expand worked
            if(!expandPirates())
            {
                return false;
            }
    }
    //made it here so we can add a pirate
    hbook[pirateCount].memberID = member;
    hbook[pirateCount].name = memberName;
    hbook[pirateCount].friendList = NULL;
    hbook[pirateCount].friendCount = 0;
    hbook[pirateCount].friendCapacity = 0;
    pirateCount++;
    return true;
    
    
}

    /* Prints the values in the list in ascending order. */
    /* This method is "const", which is a promise to the compiler
     that it won't change the value of any private variables. */
void HookBook::print() const
{
    cout << "There are " << pirateCount << " pirates in the system." << endl;
    for (size_t i = 0; i < pirateCount; i++) {
        cout << "Pirate: " << hbook[i].name << " with memberID: "
             << hbook[i].memberID << " has friends ";
        
        for(size_t j = 0; j < hbook[i].friendCount; j++)
        {
            cout << hbook[i].friendList[j] << " ";
        }
        
        cout << endl;
        
    }
}

    
 
//the function you will write you may have an empty list to start
bool HookBook::addFriend(int memID, int friendID)
{
	// find the pirate by given ID
	size_t index = 0;
	for (size_t i = 0; i<pirateCount; i++){
		if (hbook[i].memberID == memID){
			index = i;
		}
	}

	//check if pirate's friend list is initialized
	if (hbook[index].friendList == NULL){
		hbook[index].friendList = new int[INIT_CAPACITY];
		hbook[index].friendCount = INIT_CAPACITY;
	}

	//check to see if free room in friend list
	if (hbook[index].friendCount >= hbook[index].friendCapacity){
		int *newArray = new int[hbook[index].friendCapacity*2];
		for (size_t i=0; i<hbook[index].friendCount; i++){
			newArray[i] = hbook[index].friendList[i];
		}
		delete [] hbook[index].friendList;
		hbook[index].friendList = newArray;
		hbook[index].friendCapacity *= 2;
	}
	
	//add new friend to friend list
	hbook[index].friendList[hbook[index].friendCount] = friendID;
	hbook[index].friendCount ++;
	return true;
}
    
/* destructor */
HookBook::~HookBook()
{

    // first delete all the Pirate data
	for(size_t i=0; i<pirateCount; i++){
		delete [] hbook[i].friendList;
	}

    // now delete the pirates themselves
	delete [] hbook;
}

bool HookBook::expandPirates()
{
    Pirate* temp = new Pirate[currentCapacity*2];
    if(temp == NULL){
        return false;
    }
    for (size_t i = 0; i < pirateCount; i++) {
        temp[i]=hbook[i];
    }
    delete[] hbook;
    hbook = temp;
    currentCapacity = currentCapacity*2;
    return true;
}

