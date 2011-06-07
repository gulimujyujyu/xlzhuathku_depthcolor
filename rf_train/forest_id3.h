#ifndef FOREST_ID3_H
#define FOREST_ID3_H

#include "id3tree.h"
#include "item.h"

class ID3Forest 
{
public:
	ID3Forest() {numOfTrees = 0; K = -1;};
	ID3Forest( int tNum, int K);
	ID3Forest( ItemSet &trainSet, int tNum, int K);

	void set( int tNum, int K );
	
	~ID3Forest() {};

	void train( ItemSet &trainSet, int tNum, int K);
	vector<float> predict(ItemSet &trainSet, int no);
	vector<float> predict(Item item);
	//vector<float> predict(float featureArray);

	float test(ItemSet &trainSet);
	void addTree(ID3Tree tree);

	bool isEmpty();

	void write( ostream& s);
	void read( istream& s);
public:
	int numOfTrees;
	int K;
	vector<ID3Tree> forest;
};

#endif