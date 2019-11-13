/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
	root = NULL;
}

BinarySearchTree::~BinarySearchTree() {
	//deletes each tree node using post-order traversal
	post_order_delete(root);
}

void BinarySearchTree::post_order_delete(Node *node) {
	//base case: node is null
	if(node == NULL){
		return;
	}
	//recursively checks left, then right nodes
	post_order_delete(node->left);
	post_order_delete(node->right);
	//third arrival at node, deletes it
	delete node;
	return;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
	//copies tree with pre-order traversal
	root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree& BinarySearchTree::operator=
		(const BinarySearchTree &source) {
	//checks for self-assignment
	if(this != &source){
		//deletes current tree if it exists
		post_order_delete(root);

		//uses pre-order traversal to copy tree
		root = pre_order_copy(source.root);
	}
	return *this;
}

Node * BinarySearchTree::pre_order_copy(Node *node) {
	//base case: node is NULL
	if (node == NULL){
		return NULL;
	}
	//creates node to add to new tree
	Node *add = new Node();

	add->count = node->count;
	add->data = node->data;

	//goes left, then right
	add->left = pre_order_copy(node->left);
	add->right = pre_order_copy(node->right);

	//returns copied node
	return add;
}

int BinarySearchTree::find_min() {
	if(root == NULL) return INT_MIN;
	return find_min(root)->data;
}

Node *BinarySearchTree::find_min(Node *node) {
	//base case: reached left-most child
	if(node->left == NULL){
		return node;
	}
	//looks for left-most child
	return find_min(node->left);
}

int BinarySearchTree::find_max() {
	if(root == NULL) return INT_MAX;
	return find_max(root)->data;
}

Node *BinarySearchTree::find_max(Node *node) {
	//base case: reached right-most child
	if(node->right == NULL){
		return node;
	}
	//looks for right most child
	return find_max(node->right);
}

bool BinarySearchTree::contains(int value) {
	return contains(root, value);
}

bool BinarySearchTree::contains(Node *node, int value) {
	//base case: empty node
	if(node == NULL){
		return false;
	}
	//base case: node matches value
	if(node->data == value){
		return true;
	}
	//checks subtrees
	if(node->data < value){
		//curr value too low, searches right subtree
		return contains(node->right, value);
	}
	else{
		//curr value too high, searches left subtree
		return contains(node->left, value);
	}
	return false;
}

void BinarySearchTree::insert(int value) {
	insert(root, NULL, value);
}

void BinarySearchTree::insert(Node *node, Node *parent, int value) {
	//base case: empty tree
	if(root == NULL){
		//creates and populates new node to add to tree
		Node *add = new Node();
		add->right = NULL;
		add->left = NULL;
		add->data = value;
		add->count = 1;

		//set as root
		root = add;
		return;
	}
	//base case: node is null, inserts here
	if(node == NULL){
		//creates and populates new node to add to tree
		Node *add = new Node();
		add->right = NULL;
		add->left = NULL;
		add->data = value;
		add->count = 1;

		//determines which side of parent to insert
		if(value < parent->data){
			//inserts left of parent
			parent->left = add;
			return;
		}
		else{
			//inserts right of parent
			parent->right = add;
			return;
		}
	}
	//base case: node already exists
		if(node->data == value){
			//duplicates at node okay, only updates count
			node->count ++;
			return;
		}
	//checks subtrees for proper insert spot
	if(node->data < value){
		//curr value too low, checks right subtree
		insert(node->right, node, value);
	}
	else{
		//curr value too high, checks left subtree
		insert(node->left, node, value);
	}
}

bool BinarySearchTree::remove(int value) {
	return remove(root,NULL,value);
}

bool BinarySearchTree::remove(Node *node, Node *parent, int value) {
	//node does not exist
	if(node == NULL){
		return false;
	}

	//value's node was found
	if(node->data == value){
		//node has duplicate values
		if(node->count > 1){
			node->count --;
			return true;
		}
		//node has no children
		if(node->left == NULL && node->right == NULL){
			return remove_no_child(node, parent, value);
		}
		//node has 1 child
		if(node->left == NULL || node->right == NULL){
			return remove_one_child(node, parent, value);
		}
		//node has 2 children
		if(node->left != NULL && node->right != NULL){
			return remove_two_child(node, parent, value);
		}
	}
	else{
		//checks subtrees for value's node
		if(node->data < value){
			//curr node's value too low, checks right
			remove(node->right, node, value);
		}
		else{
			//curr node's value too high, checks left
			remove(node->left, node, value);
		}
	}
	return false;
}

bool BinarySearchTree::remove_no_child(Node *node, Node *parent, int value){
	//handles root case
	if(parent == NULL){
		//resets root to null
		root = NULL;
		delete node;
		return true;
	}
	//determines node's left/right relation to parent
	if(node->data > parent->data){
		//resets parent's right pointer
		parent->right = NULL;
	}
	else{
		//resets parent's left pointer
		parent->left = NULL;
	}
	delete node;
	return true;
}

bool BinarySearchTree::remove_one_child(Node *node, Node *parent, int value){
	//handles root case
	if(parent == NULL){
		if(node->left == NULL){
			//sets right child to root
			root = node->right;
			//deletes original root
			delete node;
			return true;
		}
		else{
			//sets left child to root
			root = node->left;
			//deletes original root
			delete node;
			return true;
		}
	}
	//determines node's left/right relation to parent
	if(node->data > parent->data){
		//node is RIGHT of PARENT
		if(node->left == NULL){
			//CHILD's node is on LEFT
			parent->right = node->right;
		}
		else{
			//CHILD's node is on RIGHT
			parent->right = node->left;
		}
		delete node;
		return true;
	}
	else{
		//node is LEFT of PARENT
		if(node->left == NULL){
			//CHILD's node is on RIGHT
			parent->left = node->right;
		}
		else{
			//CHILD's node is on LEFT
			parent->left = node->left;
		}
		delete node;
		return true;
	}
	return false;
}

bool BinarySearchTree::remove_two_child(Node *node, Node *parent, int value){

	//sets nodes for right child's min and it's parent
	Node *right_min = find_min(node->right);
	Node *par = find_parent(node, right_min);

	//creates temp ints for node value after right_min gets removed
	int temp_count = right_min->count;
	int temp_data = right_min->data;

	//special case: right_min has count > 1
	if(right_min->count > 1){
		//sets it's count to 1
		//allows remove() to delete entire node, not decrement
		right_min->count = 1;
		remove(right_min, par, right_min->data);
	}
	else{
		//removes right_min node
		remove(right_min, par, right_min->data);
	}

	//resets original node's attributes
  	node->count = temp_count;
  	node->data = temp_data;

  	return true;
}


int BinarySearchTree::tree_height() {
	return tree_height(root) - 1;
}

int BinarySearchTree::tree_height(Node *node) {
	//base case: tree is empty
	if(root == NULL){
		return 0;
	}
	//base case: node is empty
	if(node == NULL){
		return 0;
	}
	//calls to left and right subtrees
	int left_height = tree_height(node->left);
	int right_height = tree_height(node->right);

	//at each node, takes max height
	return 1 + std::max(left_height, right_height);
}

// returns the total number of nodes
int BinarySearchTree::node_count() {
	return node_count(root);
}

int BinarySearchTree::node_count(Node *node) {
	//base case: node is empty
	if(node == NULL){
		return 0;
	}
	//counts current node,
	//returns count with left/right subtree values
	return 1 + node_count(node->left) + node_count(node->right);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() {
	return count_total(root);
}

int BinarySearchTree::count_total(Node *node) {
	//base case: node is NULL
	if(node == NULL){
		return 0;
	}
	//counts current node total,
	//returns with left/right subtree totals
	return ((node->data) * (node->count)) +
			count_total(node->left) + count_total(node->right);
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() {
	printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node,Node *child) {
	if (node==NULL) return NULL;

	// if either the left or right is equal to the child,
	// we have found the parent
	if (node->left==child || node->right == child) {
		return node;
	}

	// Use the binary search tree invariant to walk the tree
	if (child->data > node->data) {
		return find_parent(node->right,child);
	}
	else {
		return find_parent(node->left,child);
	}
}
