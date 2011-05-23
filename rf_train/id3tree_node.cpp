#include "id3tree_node.h"

ID3TreeNode::ID3TreeNode()
{
	this->parent = -1;
	this->leftChild = -1;
	this->leftChild = true;
	this->attri = -1;
	this->thres = -1;
	this->distribution = vector<float>(CLASS_NUM);
}

void ID3TreeNode::print( ostream &out)
{
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
}