#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

	int		count;
	BTNode* root;

	// print operation for BST (same as BT)					
	void preOrderPrint2(BTNode*);	// recursive function for preOrderPrint()
	void inOrderPrint2(BTNode*);	// recursive function for inOrderPrint()
	void postOrderPrint2(BTNode*);	// recursive function for postOrderPrint()

	// sample operation (extra functions) - same as BT
	void countNode2(BTNode*, int&);		// recursive function for countNode()
	bool fGS2(type, BTNode*);					// recursive function for findGrandsons(): to find the grandfather
	void fGS3(BTNode*, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found

	// basic functions for BST
	void insert2(BTNode*, BTNode*);		// recursive function for insert() of BST
	void case3(BTNode*);					// recursive function for remove()
	void case2(BTNode*, BTNode*);		// recursive function for remove()
	bool remove2(BTNode*, BTNode*, type);	// recursive function for remove()



	// basic functions for BST
	BST();
	bool empty();
	int size();
	bool insert(type);		// insert an item into a BST
	bool remove(type);			// remove an item from a BST

	// print operation for BST (same as BT)
	void preOrderPrint();			// print BST node in pre-order manner
	void inOrderPrint();			// print BST node in in-order manner
	void postOrderPrint();			// print BST node in post-order manner
	void topDownLevelTraversal();	// print BST level-by-level

	// sample operation (extra functions) - same as BT
	int countNode();		// count number of tree nodes
	bool findGrandsons(type);	// find the grandsons of an input father item

	bool display(int, int);
	bool printSpiral();
	void inOrderWrite();			// write BST node in in-order manner to file
	void inOrderWrite2(BTNode*);	// recursive function for inOrderWrite()
	void DescOrderQueue();			// print BST node in descending order
	void DescOrderQueue2(BTNode*);	// recursive function for DescOrderQueue()
	void DescOrderWrite();			// write BST node in descending order
	void DescOrderWrite2(BTNode*);	// recursive function for DescOrderWrite()
	void inOrderQueue(Queue&, int);	// switch order of queue
	void inOrderQueue2(BTNode*, Queue&, int); // recursive function for inOrderQueue()

	int BSTheight(BTNode*);
	bool deepestNodes();
	bool insertIntoQueue(BTNode*, type);
	bool CloneSubtree(BST, type);
	bool findAncestors(BTNode*, type);
	bool printAncestor(type);

	
	

};




#endif