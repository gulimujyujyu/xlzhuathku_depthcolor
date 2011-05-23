#ifndef ID3TREE_NODE_H
#define ID3TREE_NODE_H

#include <vector>
#include <fstream>
#include "item.h"
using namespace std;

class ID3TreeNode {
public:
	ID3TreeNode();
	~ID3TreeNode() {};
	void print( ostream &out);

	//int splitThis( ItemSet &trainSet, int begin, int end);

	bool isLeaf;
	int parent;
	int leftChild;
	int attri;
	float thres;
	float entropy;
	vector<float> distribution;
};
#endif