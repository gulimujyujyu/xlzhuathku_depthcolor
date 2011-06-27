#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <fstream>
using namespace std;

#define SEEDS_ARRAY_SIZE 400
#define FEATURE_DIM (SEEDS_ARRAY_SIZE/2)
#define CLASS_NUM 7

struct Item {
	float feature[FEATURE_DIM];
	int label;
};

class ItemSet 
{
public:
	ItemSet();
	ItemSet(istream& inData, int itemNum);
	ItemSet(istream& inData, istream& inLabel, int itemNum);

	void read( istream& inData, istream& inLabel, int itemNum);
	void read( istream& inData, int itemNum);
	void write( ostream& outData, ostream& outLabel);
	void write( ostream& outData);

	void resetIdx();

public:
	int itemNum;
	int dim;
	bool isSupervised;
	vector<Item> data; 
	vector<int> idxArray;
};

#endif