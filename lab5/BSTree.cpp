#include "BSTree.h"
#include <stack>
#include <queue>



BST::BST()
{
	root = NULL;	
}

//
// Insert: public version of Insert takes a value only and
// 	   inserts in the tree at the root
//
void BST::unbalancedInsert(int v)
{
	root = unbalancedInsert(root, v);
}

//
// Insert: private version inserts a value at any subtree
//         given by the 'root' of that tree
//
//   returns: the current tree NOW WITH the value inserted
//   note: ALWAYS adds a leaf
//
BSTNode* BST::unbalancedInsert(BSTNode* r, int v)
{
	//Base Case for recursion:
	//We have reached the end of the
	//tree and we are at NULL. We
	//create a node with the correct
	//information and return a pointer
	//to the new data. This return sets
	//the value for the parent which made
	//the function call

	if(r == NULL)
	{
		r = new BSTNode;
		r->value = v;
		r->left = NULL;
		r->right = NULL;
		return r;
	}

	//notice we asked NULL first so that
	//r->left and r->right will not seg fault

	else if(v < r->value)
	{
		r->left = unbalancedInsert(r->left, v);
		return r;

	}

	else
	{
		r->right = unbalancedInsert(r->right, v);
		return r;


	}
}


//****************** inorder *****************//

void BST::inOrder()
{
	inOrder(root);		// calls the next one
}


void BST::inOrder(BSTNode* root)
{
	//TODO: your code here

	//base case NULL
	if(root == NULL){
		return;
	}
	//recursive left
	inOrder(root->left);

	//print
	cout<< root->value << " ";

	//recursive right
	inOrder(root->right);
}



//****************** postorder *****************//



void BST::postOrder()
{	
	postOrder(root);	// calls the next one
}

void BST::postOrder(BSTNode* root)
{
	//TODO: your code here --- if you want

	//base case NULL
	if(root == NULL){
		return;
	}
	else{
		//recursively check left, right
		//print on the third time a node is reached
		postOrder(root->left);
		postOrder(root->right);
		cout << root->value << " ";
	}

}
//****************** preorder *****************//



// print the tree in preOrder using the next function
// Question to ponder: can we do this without a helper function?
void BST::preOrder()
{
	preOrder(root);		// calls the next one (really needed?)
}

//
// preOrder traversal using a stack of our own, not
// the one from the compiler

void BST::preOrder(BSTNode* root)
{
	//preorder with a stack
	//TODO: stack defined here:
	stack <BSTNode*> preOrder;

	//TODO: your code here
	//make temp node and reset node
	BSTNode* temp = root;
	BSTNode* x = NULL;

	//start stack with root value
	preOrder.push(temp);

	//traverse rest of tree
	while(preOrder.size() > 0){
		//remember top number to print
		x = preOrder.top();
		//reset loop to start from that node
		temp = x;

		//pop
		preOrder.pop();

		//print
		cout<< x->value << " ";

		//push right
		if(temp->right != NULL){
			preOrder.push(temp->right);
		}

		//push left
		if(temp->left != NULL){
			preOrder.push(temp->left);
		}
	}
}



//****************** levelorder *****************//



void BST::levelOrder()
{
	levelOrder(root);
}


void BST::levelOrder(BSTNode* root)
{

	//TODO: Use a queue, declare it here
	queue<BSTNode*> level;

	//TODO: your code here

	//make temp and reset at node
	BSTNode* temp = root;
	BSTNode* x = NULL;

	//start queue with root value
	level.push(temp);

	//use loop to traverse rest of tree
	while(level.size() > 0){
		//remember top number to print
		x = level.front();

		//reset loop to start from that node
		temp = x;

		//dequeue and print
		level.pop();
		cout<< x->value << " ";

		//push left
		if(temp->left != NULL){
			level.push(temp->left);
		}
		//push right
		if(temp->right != NULL){
			level.push(temp->right);
		}
	}
}
