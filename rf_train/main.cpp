#include "item.h"
#include "id3tree.h"
#include "forest_id3.h"
#include <fstream>
#include <iostream>
#include <time.h>

#define TREE_DEPTH 15

int main()
{
	ifstream inData;
	ifstream inLabel;
	ofstream outTree;
	int traingSetSize = 7040;
	//char dataFilename[] = "data/000000.txt";
	//char labelFilename[] = "data/000000.label";
	//char treeFilename[] = "data/000000.tree";
	char dataFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000.txt";
	char labelFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000.label";
	char treeFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000.tree";
	inLabel.open( labelFilename, ios::in);
	inData.open( dataFilename, ios::in );
	outTree.open( treeFilename, ios::out);

	if( !(outTree.good())) {
		printf("open failed.");
		return -1;
	}

	if( !(inLabel.good())|| !(inData.good()))
	{
		printf("open failed.");
		return -1;
	}

	ItemSet trainSet( inData, inLabel, traingSetSize);

	printf("Read finished.\n");
	srand(time(NULL));
	ID3Tree tree(trainSet, TREE_DEPTH, 10);
	printf("Tree finished.\n");
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
	ID3Forest forest(trainSet, 5, TREE_DEPTH);
	printf("Forest finished.\n");
	
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
	
	forest.write(outTree);
	inLabel.close();
	inData.close();
	return 0;
}