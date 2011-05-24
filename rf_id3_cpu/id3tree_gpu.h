#ifndef ID3TREE_H
#define ID3TREE_H

#include <stdio.h>
#define NUM_OF_CLASSES 6
#define NUM_OF_PARAMS 500 //twice as FEATURE_DIM+1( attri + threshold)
#define NUM_OF_TREES 4
#define MAX_TREE_NODE_NUM 600

struct TreeNode {
	int idx;
	int parent;
	int leftChild;
	int isLeaf;
	int attri;
	float thres;
	float distribution[NUM_OF_CLASSES];
};

struct Tree {
	TreeNode *nodeArray;
	int numOfNodes;
};

struct Forest {
	Tree forest[NUM_OF_TREES];
};

//Training
//void trainForest(Forest *forest, float* devPtr, int itemNum, int dim);
//Reading from disk
bool readForest(const char * filename, Forest *forest);
void printForest(Forest *forest);
void copyOneNode( TreeNode *tgt, TreeNode *src);
bool readOneNode( FILE * file, TreeNode *a, int idx);
void printOneNode(TreeNode *a);
//Testing
#endif