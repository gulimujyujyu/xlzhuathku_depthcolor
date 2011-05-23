#include "forest_id3.h"
#include "id3tree.h"

ID3Forest::ID3Forest( ItemSet &trainSet, int tNum, int K)
{
	train(trainSet, tNum, K);
	this->numOfTrees = tNum;
	this->K = K;
}

void ID3Forest::train(ItemSet &trainSet, int tNum, int K)
{
	int i;
	for( i=0; i<tNum; i++) {
		trainSet.resetIdx();
		/*
		ID3Tree tree(K, -1);//(trainSet, K, -1);
		tree.train(trainSet);
		*/
		ID3Tree tree(trainSet, K, -1);
		this->forest.push_back(tree);		
	}	
}

vector<float> ID3Forest::predict(ItemSet &testSet, int no)
{
	int idx = 0;
	int treeNo;
	int attr = 0;
	float splitA = 0;
	float sumA = 0;
	vector<float> rslt(CLASS_NUM, 0);
	/*
	for( int ii = 0 ; ii < rslt.size(); ii++) {
		rslt[ii] = 0;
	}
	*/

	for( treeNo=0; treeNo<this->numOfTrees; treeNo++ ) {
		vector<float> tmp = this->forest[treeNo].predict(testSet, no);
		for( int ii = 0 ; ii < rslt.size(); ii++) {
			rslt[ii] += tmp[ii];
			sumA += tmp[ii];
		}
	}
	for( int ii = 0 ; ii < rslt.size(); ii++) {
		rslt[ii] /= sumA;
	}
	return rslt;
}

float ID3Forest::test(ItemSet &testSet)
{
	int i,j;
	int maxClass;
	float maxValue = -1;
	vector<float> a;

	float accuracy = 0;
	for ( i = 0; i < testSet.data.size(); i++) {
		a = predict(testSet, i);
		maxClass = -1;
		maxValue = -1;
		for(j=0; j<a.size(); j++) {
			if ( maxValue < a[j]) {
				maxValue = a[j];
				maxClass = j;
			}
		}
		if ( maxClass == testSet.data[i].label) {
			accuracy += 1;
		}
	}
	accuracy /= float(i);
	return accuracy;
}

void ID3Forest::addTree(ID3Tree tree)
{
	this->forest.push_back(tree);
	this->numOfTrees += 1;
}

void ID3Forest::write( ostream& s)
{
	for(int i=0 ;i < numOfTrees; i++) 
		this->forest[i].write(s);
}