#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "BST.h"
#include "Queue.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}


int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}


void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}


bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}


bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


bool BST::display(int order, int source)
{
	if (root == NULL) return false;

	if (order == 1)
	{
		if (source == 1)
		{
			inOrderPrint();
		}

		else if (source == 2)
		{
			inOrderWrite();
			cout << "Successfully display output to student-info.txt" << endl;
		}
	}
	else
	{
		if (source == 1)
		{
			DescOrderQueue();

		}

		else if (source == 2)
		{
			DescOrderWrite();
			cout << "Successfully display output to student-info.txt" << endl;
		}
	}

	return true;
}


bool BST::printSpiral() // by modify topDownlevelTraversal
{
	int line = 0, nodecount = 0, node = 0, size, id;
	BST t2 = BST();
	BTNode* cur, * temp;
	Queue q, q2, q3, tmp;
	vector<int> v;

	if (root == NULL) return false; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty())
	{
		size = q.size();
		for (int i = 1; i <= size; i++) // check size to dequeue and enqueue
		{
			q.dequeue(cur);
			q2.enqueue(cur); // store into another queue to switch order
			if (cur != NULL)
			{
				if (line == 0)
				{
					id = cur->item.id;
					v.push_back(id);

					if (cur->left != NULL)
					{
						q.enqueue(cur->left);
						node++;
					}

					if (cur->right != NULL)
					{
						q.enqueue(cur->right);
						node++;
					}
				}

				else
				{

					if (cur->left != NULL)
					{
						q.enqueue(cur->left);
						nodecount++;
					}

					if (cur->right != NULL)
					{
						q.enqueue(cur->right);
						nodecount++;
					}
				}

			}
		}

		if (line == 0)
		{
			q2.dequeue(temp); // already print, so does not need it
		}
		else
		{
			int ncount = q2.size();
			for (int i = 0; i < ncount; i++)
			{
				q2.dequeue(temp);
				q3.enqueue(temp); // use to reset the tree
				t2.insert(temp->item);
			}
			t2.inOrderQueue(tmp, line); // switch order based on level and insert into new queue
										// can use back q2, but to prevent confusion to me, so i use new queue
		}

		int num = tmp.size();
		for (int i = 0; i < num; i++)
		{
			tmp.dequeue(cur);
			id = cur->item.id;
			v.push_back(id);
			
		}

		int ncount = q3.size();
		for (int i = 0; i < ncount; i++)
		{
			q3.dequeue(temp);
			t2.remove(temp->item); // reset the tree being used to switch order
		}

		node = 0;
		nodecount = 0;
		line++;
	}

	for (int id :v)
		cout << id << ' ';  // print the data based on position
	

	return true;
}


void BST::inOrderWrite() // same with inOrderPrint but change to write to file
{
	ofstream write("student-info.txt", ios::app);

	if (root == NULL) return;// handle special case
	else inOrderWrite2(root);// do normal process
	cout << endl;
	write.close();
}


void BST::inOrderWrite2(BTNode* cur)
{
	ofstream write("student-info.txt", ios::app);

	if (cur == NULL) return;
	inOrderWrite2(cur->left);
	cur->item.print(write);
	write << endl;
	inOrderWrite2(cur->right);
}


void BST::DescOrderQueue() // Descending order print
{
	if (root == NULL) return;// handle special case
	else DescOrderQueue2(root);// do normal process
	cout << endl;
}


void BST::DescOrderQueue2(BTNode* cur) // right first then to left
{
	if (cur == NULL) return;
	DescOrderQueue2(cur->right);
	cur->item.print(cout);
	DescOrderQueue2(cur->left);
}


void BST::DescOrderWrite() // same with DescOrderPrint but change to write to file
{
	ofstream write("student-info.txt", ios::app);

	if (root == NULL) return;// handle special case
	else DescOrderWrite2(root);// do normal process
	cout << endl;
	write.close();
}


void BST::DescOrderWrite2(BTNode* cur)
{
	ofstream write("student-info.txt", ios::app);

	if (cur == NULL) return;
	DescOrderWrite2(cur->right);
	cur->item.print(write);
	write << endl;
	DescOrderWrite2(cur->left);
	write << endl;
}


void BST::inOrderQueue(Queue& queue, int num) // switch order of queue
{
	if (root == NULL) return;// handle special case
	else inOrderQueue2(root, queue, num);// do normal process
	cout << endl;

}


void BST::inOrderQueue2(BTNode* cur, Queue& queue, int num)
{
	if (cur == NULL) return;
	if (num % 2 == 0)
	{
		inOrderQueue2(cur->right, queue, num);
		queue.enqueue(cur);
		inOrderQueue2(cur->left, queue, num);
	}
	else
	{
		inOrderQueue2(cur->left, queue, num);
		queue.enqueue(cur);
		inOrderQueue2(cur->right, queue, num);
	}


}

int BST::BSTheight(BTNode* cur)
{
	int lheight = 0, rheight = 0;

	if (root == NULL)
		return 0;

	if (cur->left != NULL)
	{
		lheight = BSTheight(cur->left);
	}

	if (cur->right != NULL)
	{
		rheight = BSTheight(cur->right);
	}

	if (lheight >= rheight)
		return (lheight + 1);
	return(rheight + 1);
}

bool BST::deepestNodes()
{
	BTNode* cur;
	Queue		    q;
	int lheight = 0, rheight = 0, size = 0, height = 0, id;
	vector<int> v;

	int treeheight;
	treeheight = BSTheight(root);

	if (root == NULL) return false; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside


		size = q.size();
		height++;

		for (int i = 0; i < size; i++)
		{
			q.dequeue(cur);
			if (cur != NULL)
			{
				if (cur->left != NULL)
				{
					q.enqueue(cur->left);
				}

				if (cur->right != NULL)
				{
					q.enqueue(cur->right);
				}
			}

			if (height == treeheight)
			{
				id = cur->item.id;
				v.push_back(id);
				cout << id << ' ';
			}

		}

	}

	return true;
}

bool BST::insertIntoQueue(BTNode* cur, type item)
{
	bool LEFT, RIGHT;
	Queue q;
	int size;
	BST t2 = BST();

	if (root == NULL) return false;
	if (cur == NULL) return false;

	if (!cur->item.compare2(item))
	{
		LEFT = insertIntoQueue(cur->left, item);
		if (LEFT == false)
			RIGHT = insertIntoQueue(cur->right, item);


		return false;
	}

	else
	{
		q.enqueue(cur);
		while (!q.empty())
		{
			size = q.size();

			for (int i = 0; i < size; i++)
			{
				q.dequeue(cur);
				t2.insert(cur->item);

				if (cur != NULL)
				{
					if (cur->left != NULL)
					{
						q.enqueue(cur->left);
					}


					if (cur->right != NULL)
					{
						q.enqueue(cur->right);
					}

				}

			}

		}
	}

	t2.preOrderPrint();
	return true;
}

bool BST::CloneSubtree(BST t1, type item)
{
	BST t2 = BST();
	cout << "This is the original tree printed in pre-order." << endl;
	preOrderPrint();
	cout << "This is the cloned tree printed in pre-order." << endl;
	insertIntoQueue(root, item);
	
	return true;
}

bool BST::findAncestors(BTNode* cur, type item)
{
	bool LEFT, RIGHT;

	if (cur == NULL) return false;

	LEFT = findAncestors(cur->left, item);

	if (LEFT == false)
		RIGHT = findAncestors(cur->right, item);

	if (LEFT || RIGHT)
	{
		cout << cur->item.id << " ";
		return true;
	}

	if (cur->item.compare2(item))
		return true;
	else
		return false;

}

bool BST::printAncestor(type item)
{
	if (root == NULL) return false;

	if (item.id == root->item.id)
		cout << "This node has no ancestor." << endl;
	findAncestors(root, item);
	

	return true;
}