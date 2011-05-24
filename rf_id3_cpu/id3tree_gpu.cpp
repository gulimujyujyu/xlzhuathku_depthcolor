#include "id3tree_gpu.h"
#include <stdio.h>
#include <stdlib.h>

bool readForest(const char * filename, Forest *forest)
{
	FILE *pFile;
	int i,j;
	int treeNodeNum;
	int treeIdx = 0;
	TreeNode a;

	printf("%s\n",filename);
	pFile = fopen(filename, "r");

	if(pFile == NULL) {
		return false;
	}

	//scan
	treeIdx = 0;
	treeNodeNum = 0;
	readOneNode( pFile, &a, treeNodeNum);
	treeNodeNum += 1;
	while(readOneNode( pFile, &a, treeNodeNum)) {
		if( a.parent == -1) {
			forest->forest[treeIdx].nodeArray = (TreeNode*)malloc( treeNodeNum*sizeof(TreeNode));
			forest->forest[treeIdx].numOfNodes = treeNodeNum;
			treeNodeNum = 0;
			treeIdx ++;
		}
		treeNodeNum += 1;
	}
	printf("%d\t%d\n",treeNodeNum,treeIdx);
	forest->forest[treeIdx].nodeArray = (TreeNode*)malloc( treeNodeNum*sizeof(TreeNode));
	printf("%d\t%d\n",forest->forest[treeIdx].numOfNodes,treeIdx);
	forest->forest[treeIdx].numOfNodes = treeNodeNum;
	printf("%d\t%d\n",forest->forest[treeIdx].numOfNodes,treeIdx);

	//read data
	rewind(pFile);
	treeIdx = 0;
	treeNodeNum = 0;
	for (i=0;i<NUM_OF_TREES;i++) {
		for (j=0;j<forest->forest[i].numOfNodes;j++) {
			readOneNode( pFile, &a, treeNodeNum);
			copyOneNode(&(forest->forest[i].nodeArray[j]), &a);
		}
	}
	
	fclose(pFile);
	return true;
}

void printForest(Forest *forest)
{
	int i, j;
	for (i=0;i<NUM_OF_TREES;i++) {
		for (j=0;j<forest->forest[i].numOfNodes;j++) {
			printOneNode( &(forest->forest[i].nodeArray[j]));
		}
	}
}

void copyOneNode( TreeNode *tgt, TreeNode *src)
{
	int i=0;
	tgt->parent = src->parent;
	tgt->leftChild = src->leftChild;
	tgt->isLeaf = src->isLeaf;
	tgt->attri = src->attri;
	tgt->thres = src->thres;
	for( i=0; i<NUM_OF_CLASSES;i++) {
		tgt->distribution[i] = src->distribution[i];
	}
}

bool readOneNode( FILE * file, TreeNode *a, int idx)
{
	/*
	out << this->parent << "\t" 
	<< this->leftChild << "\t"
	<< this->isLeaf << "\t"
	<< this->attri << "\t"
	<< this->thres << "\t";
	for (int i=0; i<this->distribution.size(); i++)
	{
	out << this->distribution[i] << "\t";
	}
	out << endl;
	*/
	bool eofReached;
	eofReached = (fscanf( file, "%d", &(a->parent)) == EOF);
	if( eofReached) return false;
	eofReached = (fscanf( file, "%d", &(a->leftChild)) == EOF);
	if( eofReached) return false;
	eofReached = (fscanf( file, "%d", &(a->isLeaf)) == EOF);
	if( eofReached) return false;
	eofReached = (fscanf( file, "%d", &(a->attri)) == EOF);
	if( eofReached) return false;
	eofReached = (fscanf( file, "%f", &(a->thres)) == EOF);
	if( eofReached) return false;
	for( int i=0; i<NUM_OF_CLASSES;i++) {
		eofReached = (fscanf( file, "%f", &(a->distribution[i])) == EOF);
		if( eofReached) return false;
	}
	return true;
}

void printOneNode(TreeNode *a)
{
	/*
	out << this->parent << "\t" 
	<< this->leftChild << "\t"
	<< this->isLeaf << "\t"
	<< this->attri << "\t"
	<< this->thres << "\t";
	for (int i=0; i<this->distribution.size(); i++)
	{
	out << this->distribution[i] << "\t";
	}
	out << endl;
	*/
	bool eofReached;
	int i=0;

	printf( "%d ", a->parent);
	printf( "%d ", a->leftChild);
	printf( "%d ", a->isLeaf);
	printf( "%d ", a->attri);
	printf( "%f ", a->thres);
	for( i=0; i<NUM_OF_CLASSES;i++) {
		printf("%f ", a->distribution[i]);
	}
	printf( "\n");
}