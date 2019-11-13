-----------------------=
-- README COMP 15 HW3 --
--    SETS & QUEUES   --
--     14 OCT 2014    --
-----------------------=

------------=
-- PURPOSE -- 
------------=

~ hw3 contains functions to model a course enrollement system

~ complete with seperate waitlists for course majors and non-majors

----------=
-- FILES --
----------=

~Student.h
	Struct definition of a Student, containing name and major bool
	
~Set.h
	Set definition of class roster, a dynamic array of students
	
~Set.cpp
	Function definitions for class manulipation
	Inlcudes add, drop, is enrolled, print, size

~Queue.h
	Queue definition for major and non major waitlists, a dynamic array of students
	Custom definitions instead of STL

~Queue.cpp
	Function definitions for queue operations including enqueue, dequeue, is empty
	* The dequeue function removes as well as returns the first in line

~IsisCourse.h
	Contains the class IsisCourse with functions for course enrollment modeling
	Functions include enrolling/dropping students, checking waitlist positions, etc.

~IsisCourse.cpp
	Function definitions for IsisCourse class modeling

~main.cpp
	Creates a sample course, enrolls students, puts overflow on waitlists
	Increases the course sizes, lets in students from waitlists accordingly

------------=
-- COMPILE --
------------=

~ Use included Makefile to compile hw3

-------------------=
-- DATA STRUCTURE --
-------------------=

~ hw3 is written using a set for the class roster and queues for the major and non-major waitlists

~ Both of the above are built using dynamic arrays of student structs

~ Originally compiled and tested with the clang++ compiler in Eclipse

--------------=
-- ALGORITHM --
--------------=

~ Any function that involves searching through a queue was accomplished with a temp queue

~ Items were dequeued from the original, checked for the search target, and added to a temp queue

~ When finished checking the entire queue, all items were dequeued from the temp, then enqueued in order back to the original queue
	
-----------=
-- THANKS --
-----------=

~ Thanks to TA Chad Myles for help debugging IsisCourse::print_list()

~ Thanks to TA Brett Fouss for help debugging main.cpp output

