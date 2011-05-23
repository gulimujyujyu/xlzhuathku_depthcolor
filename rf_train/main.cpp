#include "item.h"
#include "id3tree.h"
#include "forest_id3.h"
#include <fstream>
#include <iostream>
#include <time.h>

int main()
{
	ifstream inData;
	ifstream inLabel;
	char dataFilename[] = "data/000000.txt";
	char labelFilename[] = "data/000000.label";
	inLabel.open( labelFilename, ifstream::in);
	inData.open(dataFilename, ifstream::in );
	if( !(inLabel.good())|| !(inData.good()))
	{
		printf("open failed.");
		return -1;
	}

	ItemSet trainSet( inData, inLabel, 270);

	srand(time(NULL));
	ID3Tree tree(trainSet, 10, 10);
	/*
	trainSet.resetIdx();
	srand(time(NULL));
	tree.write(cout);
	ID3Tree tree1(trainSet, 4, 10);
	trainSet.resetIdx();
	tree1.write(cout);
	ID3Tree tree2(trainSet, 4, 10);
	trainSet.resetIdx();
	tree2.write(cout);
	ID3Tree tree3(trainSet, 4, 10);
	trainSet.resetIdx();
	tree3.write(cout);
	ID3Tree tree4(trainSet, 4, 10);
	trainSet.resetIdx();
	tree4.write(cout);
	*/
	ID3Forest forest(trainSet, 20, 10);
	
	/*
	forest.addTree(tree);
	forest.addTree(tree1);
	forest.addTree(tree2);
	forest.addTree(tree3);
	forest.addTree(tree4);
	*/

	cout << tree.test( trainSet) << endl;
	/*
	cout << tree1.test( trainSet) << endl;
	cout << tree2.test( trainSet) << endl;
	cout << tree3.test( trainSet) << endl;
	cout << tree4.test( trainSet) << endl;
	*/
	cout << forest.test( trainSet) << endl;
	
	//forest.write(cout);
	inLabel.close();
	inData.close();
	return 0;
}