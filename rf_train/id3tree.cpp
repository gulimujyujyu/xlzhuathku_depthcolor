#include "id3tree.h"
#include "id3tree_node.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "item.h"

#define MAX_ATTRIBUTE_VALUE 999999
#define MIN_ATTRIBUTE_VALUE -999999
#define HISTO_BINS 8

ID3Tree::ID3Tree(ItemSet &trainSet, int maxDepth, int K)
{
	this->maxDepth = maxDepth;
	this->K = K;
	this->dim = trainSet.dim;
	this->attributesPerRound = ATTRIBUTES_PER_ROUND;
	this->train(trainSet);
}

bool myCompare (AttrMapping i,AttrMapping j) { return (i.value>j.value); }

vector<int> ID3Tree::generate_attributes(int idx)
{
	vector<AttrMapping> fallInto(dim);
	int i=0;
	for( i=0; i< dim; i++) {
		fallInto[i].idx = i;
		fallInto[i].value = 0;
	}

	int sampleTimes = (this->attributesPerRound)*2;
	if ( dim < 10) {
		sampleTimes += 10;
	}

	srand(time(NULL));
	for ( i=0; i<sampleTimes; i++) {
		fallInto[rand()%dim].value += 1;
	}

	sort( fallInto.begin(), fallInto.end(), myCompare);

	//harvest
	vector<int> attrIdx;
	int tmpIdx;
	int count = 0;
	for ( i=0; i<dim; i++) {
		tmpIdx = fallInto[i].idx;
		if ( checkAttri(idx, tmpIdx) && fallInto[i].value > 0 && count < this->attributesPerRound) {
			attrIdx.push_back(tmpIdx);
			count ++;
		}
	}

	return attrIdx;
}

bool ID3Tree::checkAttri(int idx, int tmpIdx)
{
	bool status = true;
	int id = idx;
	do {
		if ( this->tree[id].attri == tmpIdx) {
			status = false;
		}
		id = tree[id].parent;
	}while(id > 0);
	return status;
}

void ID3Tree::mark_as_leaf( ItemSet &trainSet, int idx, int depth, int start, int end)
{
	int j;
	float sum = 0;
	for( j=start; j<end; j += 2) {
		this->tree[idx].distribution[trainSet.data[trainSet.idxArray[j]].label] += 1;
		sum += 1;
	}
	for ( j=0; j<CLASS_NUM; j++) {
		this->tree[idx].distribution[j] /= sum;
	}
	this->tree[idx].leftChild = -1;
	this->tree[idx].isLeaf = true;
}

void ID3Tree::mark_as_branch( int idx)
{
	ID3TreeNode leftChild;
	leftChild.parent = idx;
	leftChild.leftChild = -1;
	leftChild.isLeaf = false;
	this->tree.push_back(leftChild);
	this->tree[idx].leftChild = this->tree.size()-1;
	ID3TreeNode rightChild;
	rightChild.parent = idx;
	rightChild.leftChild = -1;
	rightChild.isLeaf = false;
	this->tree.push_back(rightChild);
}

inline float calcEn( float histo[], int size)
{
	float a = 0;
	for ( int i=0; i<size; i++) {
		a += ((histo[i] == 0)? 0:(- histo[i] * log(histo[i])));
	}
	return a;
}

int ID3Tree::find_best_split( ItemSet &trainSet, vector<int> &attrib, int start, int end, int idx)
{
	int i=0, j=0;
	int att ;
	int bin;
	float maxA;
	float minA;
	float tmpA;
	float rangeA;
	float sumHisto;
	float sumHisto1;
	float histo[HISTO_BINS];
	float histo1[CLASS_NUM];
	float histo2[CLASS_NUM];
	float bestThres;
	float bestGain = 100;
	float splitA = 0;
	int splitAtt ;
	for (i=0; i< attrib.size(); i++) {
		//hypothesis
		maxA = MIN_ATTRIBUTE_VALUE;
		minA = MAX_ATTRIBUTE_VALUE;
		att = attrib[i];
		
		//first pass: find min, max
		for ( j=start; j<end; j++) {
			tmpA = trainSet.data[trainSet.idxArray[j]].feature[att];
			maxA = tmpA>maxA? tmpA: maxA;
			minA = tmpA<minA? tmpA: minA;
		}
		rangeA = maxA - minA;
		if (rangeA <= 0) {
			//no discriminative power;
			continue;
		}
		//second pass: quantize
		memset(histo, 0, HISTO_BINS*sizeof(float));
		sumHisto = 0;
		for ( j=start; j<end; j++) {
			tmpA = trainSet.data[trainSet.idxArray[j]].feature[att];
			bin = int((tmpA-minA)*HISTO_BINS*0.95/rangeA);
			histo[bin] += 1;
			sumHisto += 1;
		}
		
		tmpA = 0 ;
		for( j=0; j<HISTO_BINS; j++) {
			tmpA += histo[j];
			if ( tmpA >= 0.5*sumHisto) {
				break;
			}
		}

		tmpA = minA + rangeA*float(j)/HISTO_BINS/0.95;
		//third pass: calculate gain
		memset(histo1, 0, CLASS_NUM*sizeof(float));
		memset(histo2, 0, CLASS_NUM*sizeof(float));
		sumHisto = 0;
		sumHisto1 = 0;
		for ( j=start; j<end; j++) {
			if(trainSet.data[trainSet.idxArray[j]].feature[att] > tmpA) {
				histo1[trainSet.data[trainSet.idxArray[j]].label] += 1;
				sumHisto += 1;
			} else {
				histo2[trainSet.data[trainSet.idxArray[j]].label] += 1;
				sumHisto1 += 1;
			}
		}
		for ( j=0; j <CLASS_NUM; j++) {
			histo1[j] /= sumHisto;
			histo2[j] /= sumHisto1;
		}

		//test
		float tmpGain = (sumHisto/(sumHisto+sumHisto1))*calcEn( histo1, CLASS_NUM) 
			+ (sumHisto1/(sumHisto+sumHisto1))*calcEn( histo2, CLASS_NUM);
		if (bestGain > tmpGain) {
			bestGain = tmpGain;
			splitA = tmpA;
			splitAtt = att;
		}
	}

	if ( bestGain==-1){
		return end;
	}
	//move data
	int hd = start;
	int tl = end-1;
	int tmpPos;
	for ( j = start; j < tl; ){
		if (trainSet.data[trainSet.idxArray[j]].feature[splitAtt] > splitA) {
			tmpPos = trainSet.idxArray[j];
			trainSet.idxArray[j] = trainSet.idxArray[tl];
			trainSet.idxArray[tl] = tmpPos;
			tl--;
		} else {
			j++;
		}		
	}
	/*
	cout << splitAtt << "\t" << splitA << endl;
	for( j=start; j<end; j += 2) {
		cout << trainSet.data[trainSet.idxArray[j]].feature[splitAtt] << endl;
	}
	*/
	float summ = 0;
	for( j=start; j<end; j += 2) {
		this->tree[idx].distribution[trainSet.data[trainSet.idxArray[j]].label] += 1;
		summ += 1;
	}
	for ( j=0; j<CLASS_NUM; j++) {
		this->tree[idx].distribution[j] /= summ;
	}
	this->tree[idx].attri = splitAtt;
	this->tree[idx].thres = splitA;
	return tl+1;
}

void ID3Tree::train(ItemSet &trainSet)
{
	if ( maxDepth < 1) {
		return;
	}
	ID3TreeNode root;
	root.parent = -1;
	root.isLeaf = false;
	this->tree.push_back(root);
	build_node(trainSet, -1, 0, 0, 0, trainSet.itemNum);
}

float ID3Tree::calculate_entropy(ItemSet &trainSet, int start, int end)
{
	float histo[CLASS_NUM] = {0};
	float sumHisto = 0;
	int j;
	for ( j=start; j<end; j++) {
		histo[trainSet.data[trainSet.idxArray[j]].label] += 1;
		sumHisto += 1;
	}
	for ( j=0; j <CLASS_NUM; j++) {
		histo[j] /= sumHisto;
	}
	return calcEn( histo, CLASS_NUM);
}

void ID3Tree::build_node(ItemSet &trainSet, int parent, int idx, int depth, int start, int end)
{
	//return
	if ( depth >= maxDepth)	{
		mark_as_leaf(trainSet, idx, depth, start, end);
		return;
	}
	vector<int> attrib = generate_attributes(idx);
	float entropy = calculate_entropy(trainSet, start, end);
	int splitPoint = find_best_split(trainSet, attrib, start, end, idx);
	if( splitPoint < end) {
		mark_as_branch(idx);
		int curSize = this->tree.size();
		build_node(trainSet, idx, curSize-2, depth+1, start, splitPoint);
		build_node(trainSet, idx, curSize-1, depth+1, splitPoint, end);
	} else {
		mark_as_leaf(trainSet, idx, depth, start, end);
	}
}

void ID3Tree::print(ostream &out)
{
	int i=0;
	for( i=0; i<this->tree.size(); i++) {
		this->tree[i].print( out);
	}
}

vector<float> ID3Tree::predict(ItemSet &testSet, int no)
{
	int idx = 0;
	int attr = 0;
	float splitA = 0;
	while( this->tree[idx].isLeaf == false) {
		attr = this->tree[idx].attri;
		splitA = this->tree[idx].thres;
		if ( testSet.data[no].feature[attr] > splitA) {
			//right
			idx = this->tree[idx].leftChild+1;
		} else {
			//left
			idx = this->tree[idx].leftChild;
		}
	}
	return this->tree[idx].distribution;
}

float ID3Tree::test(ItemSet &testSet)
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