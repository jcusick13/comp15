-----------------------=
-- README COMP 15 HW4 --
-- BINARY SEARCH TREE --
--     26 OCT 2014    --
-----------------------=

------------=
-- PURPOSE -- 
------------=

~ hw4 contains functions to model a binary search tree

~ contains functions to help add, remove, search, etc.


----------=
-- FILES --
----------=

~BinarySearchTree.h
	Contains function declarations for a Node struct and functions for adding/removing
	
~BinarySearchTree.cpp
	Function definitions for a binary search tree
	Functions include find min, insert, remove, tree height, etc.

~main.cpp
	Creates a binary search tree, makes a copy with copy constructor
	Removes individual nodes from the tree
	Uses copy constructor each time to reset tree in between removes

------------=
-- COMPILE --
------------=

~ Use included Makefile to compile hw4

-------------------=
-- DATA STRUCTURE --
-------------------=

~ hw4 is a binary search tree, comprised of nodes with a value and value count attribute

~ Originally compiled and tested with the clang++ compiler in Eclipse

--------------=
-- ALGORITHM --
--------------=

~ All functions are called using recursion

~ Inserting nodes simply added them as leaves

~ Remove was created with three helper functions for each special case
	-- Node with no children
			= The node was simply deleted
	-- Node with one child
			= The node was bypassed by connecting it's parent to child
	-- Node with two children
			== Node was replaced with min node of right child
			== Right child's min node was then deleted
