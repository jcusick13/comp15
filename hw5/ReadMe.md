-----------------------=
-- README COMP 15 HW5 --
--      SORTING       --
--    14 NOV 2014     --
-----------------------=

------------=
-- PURPOSE --
------------=

~ hw5 contains three sorting functions to order lists of integers

~ Selection sort, Quick sort, and Insertion sort are used

----------=
-- FILES --
----------=

~ SelectionSort.h
		Contains function declarations for a selection sort and outputing
		
~ SelectionSort.cpp
		Function definitions for an in-place selection sort and an output to the console
		
~ main1.cpp
		Waits for an input list of integers, sorts them lowest to highest, and outputs them to the console
		
			
			
~ sort2.h
		Contains function declarations for a quick sort and outputing
		
~ sort2.cpp
		Function definitions for an in-place quick sort and an output to the console
		
~ main2.cpp
		Waits for an input list of integers, sorts them lowest to highest, and outputs them to the console



~ sort3.h
		Contains function declarations for sorting and outputting

~ sort3.cpp
		Function definitions for an in-place insertion sort and an output to the console
		
~ main3.cpp
		Waits for an input list of integers, sorts them lowest to highest, and outputs them to the console

------------=
-- COMPILE --
------------=

~ Use included Makefile to compile hw5

-------------------=
-- DATA STRUCTURE --
-------------------=

~ All of the sorting functions take in a struct which has two int members: length and a pointer to an array

~ Originally compiled and tested with the clang++ compiler in Eclipse

--------------=
-- ALGORITHM --
--------------=

--> In Place Selection Sort
		~ For each element in an array, it traverses all entries to the right and finds the lowest remaining element. The current element and the lowest element are then swapped in place.
		~ This ensures that everything to the left of the current element is already in sorted order.
		~ The algorithm continues right until the end of the (now sorted) list is reached.
		~
			->	PERFORMANCE
			== Best case performance ...... O(n^2)
			== Average case performance ... O(n^2)
			== Worst case performance ..... O(n^2)
			-> 	SPACE
			== Worst case storage ......... O(n)
		~
		~ The best, worst, and average case are all O(n^2) because while the algorithm is searching for the current min, it is never certain about it until it reaches the end of the list. That means that even when given a correcly sorted list to start, a selection sort still be O(n^2) because it will have to traverse the entire list every time it's trying to find a min.
		~ The space requirements for this sort are pretty good, since all elements are swapped in place. An extra space is needed to complete the swap, but this O(1) storage is ignored in the long run, and it's worse case storage becomes O(n).
		~ Selection sort's only redeeming quaility aside from it's storage size is it's terseness. It is short and easy to write, but should never be implemented in a program.


--> In Place Quick Sort
		~ This is an example of a divide and conquer sorting algorithm, which means that this splits the array into smaller pieces and then recursively works on those smaller and smaller pieces.
		~ The array is divided according to a PIVOT value. After each round of sorting, all values to the left of the pivot are lower and all values to the right are higher.
		~ The choice of the pivot is incredibly important because, while O(n^2) behavior is very rare with quick sort, a poor pivot location will make that happen (see discussion below chart). The best choice is a pseudo random or middle number of the array every time. 
		~ The second part of this algorithm deals with PARTITIONING the data. 
		~ Two markers (right and left) start at the right and left ends of the array. The right marker will check if it's value should be to the left of the pivot, and shifts over to the left until this becomes true and stays there. The left marker will do the opposite, searching right for values that should be on the right of the pivot. Once both right and left and done moving, they swap values with each other. They then begin the process over again until the are at the same array index.
		~ When left == right, that value is swapped with the pivot, and the array is broken up into two new arrays - one from the left up to but not including the pivot, and then from the pivot to the right. 
		~ The algorithm is called recursively until an array size of 0 or 1 is reached, since these are considered to be already sorted.
		~
			->	PERFORMANCE
			== Best case performance ...... O(nlogn)
			== Average case performance ... O(nlogn)
			== Worst case performance ..... O(n^2)
			->	SPACE
			== Average case storage .......	O(logn)
			== Worst case storage .........	O(n)
		~
		~ If just the first number in a sorted array is used for the pivot, the array will always be divided into an array of just the pivot and another array of every other number, therefore going through every element, giving O(n^2) complexity. Using a middle number or a psuedo random number will avoid this, ensuring that on average, for each element, you will only have log(n) recursive calls, giving an average and best behavior of O(nlogn).
		~ If choosing to use the middle number for the pivot, (left + (right-left)/2) is used instead of (right+left)/2. The latter equation creates the chance for a stack overflow if you are dealing with large enough arrays. The former equation ensures that any number used is smaller or equal to existing ones. 
		~ Avoiding the worst case behavior, which would also yield a new array for every element O(n), the average space storage needed is just log(n), due to splitting the array in half with every recursive call.


--> In Place Insertion Sort
		~ Stable and in place sorting algorithm that for every element in the list starting at the left:
			~ Swaps it with the element to the left if the left element is larger
			~ Continues this until the element to the left of the one being swapped is either NULL (making the current one the first in the array) or until the one being swapped is larger than the element to the left
			~
				->	PERFORMANCE
				== Best case performance ...... O(n)
				== Average case performance ... O(n^2)
				== Worst case performance ..... O(n^2)
				-> 	SPACE
				== Worst case storage ......... O(n)
			~
			~ It's worst case performance would be a reverse ordered array. This would mean that for every element in the array, it would have to slide every single element before it over one before it could return the original element to it's correct place. Not a trivial task!
			~ In the case that the elements are in order, no swapping would occur, as the algorithm would just read through the array once, giving O(n) complexity. This leads to very fast performance for sorted or nearly-sorted arrays. The insertion sort can be successfully used in situations where the data are managed to be nearly ordered, especially in examples like TimSort which uses an insertion sort on splices of it's data that are nearly sorted.
			~ This has the same storage complexity as the in-place selection sort. There is one extra space required to complete the swap, O(1), but in the long run, the worst case space storage becomes O(n).

Sources: http://en.wikipedia.org/wiki/Selection_sort
~		http://en.wikipedia.org/wiki/Quicksort
~		http://en.wikipedia.org/wiki/Timsort
~		http://en.wikipedia.org/wiki/Insertion_sort
~		http://www.cs.tufts.edu/comp/15/lectures/Day_15/Day15.pdf
~		http://www.cs.tufts.edu/comp/15/lectures/Day_16/Day16.pdf
		