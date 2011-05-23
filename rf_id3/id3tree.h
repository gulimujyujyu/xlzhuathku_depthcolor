#ifndef ID3TREE_H
#define ID3TREE_H

#define NUM_OF_CLASSES 15
#define NUM_OF_PARAMS 15
#define NUM_OF_TREES 3

struct TreeNode {
	float idx;
	float leftChildIdx;
	float isLeafNode;
	float parameters[NUM_OF_PARAMS];
	float distribution[NUM_OF_CLASSES];
};

struct Tree {
	TreeNode root;
	int maxDepth;
	int seed;
};

struct Forest {
	Tree forest[NUM_OF_TREES];
};

//Training
void trainForest(Forest *forest, float* devPtr, int itemNum, int dim);
void buildOneNode();
void findBestSplit();
void envolveTrainingSet();
//Testing
#endif