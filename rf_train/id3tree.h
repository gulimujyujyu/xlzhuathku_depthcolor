#ifndef ID3TREE_H
#define ID3TREE_H

#include "id3tree_node.h"
#include "item.h"
#include <fstream>
using namespace std;
//TODO: printing
#define ATTRIBUTES_PER_ROUND 10

struct AttrMapping{
	int idx;
	int value;
};

class ID3Tree {
public:
	ID3Tree() {};
	ID3Tree( ItemSet &trainSet, int maxDepth, int K);

	void train(ItemSet &trainSet);
	vector<int> generate_attributes(int idx);
	void build_node(ItemSet &trainSet, int parent, int idx, int depth, int start, int end);
	float calculate_entropy(ItemSet &trainSet, int start, int end);
	int find_best_split(ItemSet &trainSet, vector<int> &attrib, int start, int end, int idx);
	void mark_as_leaf(ItemSet &trainSet, int idx, int depth, int start, int end);
	void mark_as_branch( int idx);
	bool checkAttri(int idx, int tmpIdx);

	void print( ostream&out);

	float test(ItemSet &testSet);
	vector<float> predict(ItemSet &testSet, int no);
private:
	vector<ID3TreeNode> tree;
	int dim;
	int maxDepth;
	int attributesPerRound;
	int K;
};
#endif