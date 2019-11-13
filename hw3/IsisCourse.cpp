/*
 * IsisCourse.cpp
 *
 */

#include <iostream>
#include "IsisCourse.h"
#include <cstdlib>

using namespace std;

IsisCourse::IsisCourse() {
	class_capacity = 0; // no students allowed in yet
}

IsisCourse::IsisCourse(int init_capacity) {
	// TODO: Student writes code here

	//create class
	class_capacity = init_capacity;
}

IsisCourse::~IsisCourse() {
	// nothing to do
}

void IsisCourse::set_class_cap(int cap) {
	class_capacity = cap;
	if (roster.size() < class_capacity) {
		update_enrollments();
	}
}

IsisCourse::ENROLLMENT_STATUS IsisCourse::enroll_student(Student s) {
	// See the enrollment logic from the assignment handout or
	// the IsisCourse.h file!
	// TODO: Student writes code here

	//handle MAJORS
	if(s.major == true){
		//try to enroll in class
		if(get_roster_size() < get_class_cap()){
			roster.add(s);
			return ENROLLMENT_STATUS(1);
		}
		//class full, add to major wait list
		else{
			major_waitlist.enqueue(s);
			return ENROLLMENT_STATUS(2);
		}
	}
	//handle NON MAJORS
	else{
		//place directly on waiting list
		other_waitlist.enqueue(s);
		return ENROLLMENT_STATUS(3);
	}
}

bool IsisCourse::drop_student(Student s) {
	bool found_student = false; // if we find the student to drop
	// TODO: Student writes code here

	//drop from CLASS
	if(roster.drop(s)){
		return true;
	}
	//drop from waitlist
	else{
		//create temp queue, student
		Queue temp;
		Student holder;

		// drop from MAJOR waitlist
		if(s.major){
			//move elements to temp queue
			while(major_waitlist.is_empty() == false){
				holder = major_waitlist.dequeue();
				if(holder.name == s.name){
					//found s, don't add to temp queue
					//update found student
					found_student = true;
				}
				//add to temp queue
				else{
					temp.enqueue(holder);
				}
			}
			//return
			while(temp.is_empty() == false){
				//remove from temp
				holder = temp.dequeue();
				//add to major waitlist
				major_waitlist.enqueue(holder);
			}

		}

		//drop from OTHER waitlist
		else{
			//move elements to temp queue
			while(other_waitlist.is_empty() == false){
				holder = other_waitlist.dequeue();
				if(holder.name == s.name){
					//found s, don't add to temp queue
					//update found student
					found_student = true;
				}
				//add to temp queue
				else{
					temp.enqueue(holder);
				}
			}
			//return
			while(temp.is_empty() == false){
				//remove from temp
				holder = temp.dequeue();
				//add to other waitlist
				other_waitlist.enqueue(holder);
			}
		}
	}
	// if we dropped a student, there should be room on
	// the roster
	update_enrollments();
	return found_student;

}

int IsisCourse::waitlist_position(ENROLLMENT_STATUS status, Student s){
	// TODO: Student writes code here

	//create counter & ans variable, student holder, temp queue
	int counter = 0;
	int ans = -1;
	Student compare;
	Queue temp;


	//go through major waitlist
	if(status == MAJOR_WAITLIST){
		//remove from major list
		while(major_waitlist.is_empty() == false){
			compare = major_waitlist.dequeue();
			counter ++;
			//check for s
			if(compare.name == s.name){
				//remember waitlist position
				ans = counter;
			}
			//add to temp queue
			temp.enqueue(compare);
		}
		//return students from temp to major wait list
		while(temp.is_empty() == false){
			compare = temp.dequeue();
			major_waitlist.enqueue(compare);
		}

		//return waitlist position
		return ans;
	}
	//go through other waitlist
	else{
		//remove from other list
		while(other_waitlist.is_empty() == false){
			compare = other_waitlist.dequeue();
			counter ++;
			//check for s
			if(compare.name == s.name){
				//remember waitlist position
				ans = counter;
			}
			//add to temp queue
			temp.enqueue(compare);
		}
		//return students from temp to other wait list
		while(temp.is_empty() == false){
			compare = temp.dequeue();
			other_waitlist.enqueue(compare);
		}

		//return waitlist position
		return ans;
	}

	//incorrect waitlist type given, return -1
	return ans;
}

IsisCourse::ENROLLMENT_STATUS IsisCourse::status(Student s) {
	// returns an ENROLLMENT_STATUS that says which list
	// (or none) that the student is on.

	// TODO: Student writes code here

	//------------------
	//search ROSTER
	if(roster.is_enrolled(s)){
		return ENROLLMENT_STATUS(1);
	}

	//NOT in ROSTER, prepare for searching thru waitlists

	//create temp q, student, answer marker for reference
	Queue temp;
	Student stud;
	Student answer;

	//---------------------
	//search MAJOR WAITLIST
	if(s.major){
		//remove all and add to temp queue, check each for s
		while(major_waitlist.is_empty() == false){
			stud = major_waitlist.dequeue();
			//check for student s
			if(stud.name == s.name){
				//remember s for return later
				answer = stud;
			}
			//add to temp queue
			temp.enqueue(stud);
		}

		//return all students to major waitlist from temp queue
		while(temp.is_empty() == false){
			//remove from temp
			stud = temp.dequeue();
			//add to major waitlist
			major_waitlist.enqueue(stud);
		}

		//if student found, return enum MAJOR, exit
		if(answer.name == s.name){
			return ENROLLMENT_STATUS(2);
		}
		else{
			//not found, return enum NONE
			return ENROLLMENT_STATUS(0);
		}
	}

	//--------------------
	//search OTHER WAITLIST
	else{
		//remove all and add to temp queue
		while(other_waitlist.is_empty() == false){
			stud = other_waitlist.dequeue();

			//check for student s
			if(stud.name == s.name){
				//remember s for return later
				answer = stud;
			}
			//add to temp queue
			temp.enqueue(stud);
		}
		//return all students to other wait list queue
		while(temp.is_empty() == false){
			//remove from temp
			stud = temp.dequeue();
			//add to other waitlist
			other_waitlist.enqueue(stud);
		}
		//if student found, return enum OTHER
		if(answer.name == s.name){
			return ENROLLMENT_STATUS(3);
		}
		//student not found anywhere, return enum NONE
		else{
			return ENROLLMENT_STATUS(0);
		}
	}
}

void IsisCourse::print_list(ENROLLMENT_STATUS status) {
	Queue *waitlist_queue;
	Queue temp_queue;
	if (status == ENROLLED) {
		roster.print_class();
		return;
	}
	if (status == MAJOR_WAITLIST) {
		waitlist_queue = &major_waitlist;
	}
	else {
		waitlist_queue = &other_waitlist;
	}
	// now handle printing the queue

	// TODO: Student writes code here
	Student temp_stud;

	//dequeue all students from wait list to a temp queue
	while(waitlist_queue->is_empty() == false){
		temp_stud = waitlist_queue->dequeue();
		temp_queue.enqueue(temp_stud);
	}

	//return students to original queue
	//print each as they are being returned
	while(temp_queue.is_empty() == false){
		temp_stud = temp_queue.dequeue();
		waitlist_queue->enqueue(temp_stud);
		cout << waitlist_position(status, temp_stud) << ". ";
		cout << temp_stud.name << "\n";
	}
}

void IsisCourse::update_enrollments() {
	// put students from the waitlists into the class
	// in priority (majors first, then others), up to
	// the class capacity.

	// TODO: Student writes code here

	//make temp student holder
	Student temp;

	//if room in roster, add to class
	while(get_roster_size() < class_capacity){
		//add major students first
		if(major_waitlist.is_empty() == false){
			temp = major_waitlist.dequeue();
			roster.add(temp);
		}
		//major queue empty
		else{
			//add other students
			if(other_waitlist.is_empty() == false){
				temp = other_waitlist.dequeue();
				roster.add(temp);
			}
			//other queue empty, quit loop
			else{
				break;
			}
		}
	}
}
