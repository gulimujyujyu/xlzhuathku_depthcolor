#include "item.h"

ItemSet::ItemSet()
{

}

ItemSet::ItemSet(istream& inData, int itemNum) 
{
	read(inData, itemNum);
}

ItemSet::ItemSet(istream& inData, istream& inLabel, int itemNum) 
{
	read(inData, inLabel, itemNum);
}

void ItemSet::read(  istream& inData, int itemNum )
{
	for (int i=0; i<itemNum; i++)
	{
		if( !(i%10000)) {
			printf("%d\n",i);
		}
		Item tmp;
		for (int j=0; j<FEATURE_DIM; j++)
		{
			inData >> tmp.feature[j];
		}
		
		data.push_back(tmp);
		idxArray.push_back(i);
	}
}

void ItemSet::read(  istream& inData, istream& inLabel, int itemNum )
{
	int jj = 0;
	for (int i=0; i<itemNum; i++)
	{
		if( !(i%10000)) {
			printf("%d\n",i);
		}
		Item tmp;
		for (int j=0; j<FEATURE_DIM; j++)
		{
			inData >> tmp.feature[j];
		}
		inLabel >> tmp.label;

		if( tmp.label < 0) {
			continue;
		}

		data.push_back(tmp);
		idxArray.push_back(jj);
		jj++;
	}
	this->dim = FEATURE_DIM;
	this->itemNum = data.size();
	this->isSupervised = true;
}

void ItemSet::resetIdx()
{
	for ( int i=0; i<(idxArray.size()); i++)
	{
		idxArray[i] = i;
	}
}

void ItemSet::write(  ostream& outData)
{
	for (int i=0; i<itemNum; i++)
	{
		for (int j=0; j<FEATURE_DIM; j++)
		{
			outData << data[i].feature[j] << "\t";
		}
	}
}

void ItemSet::write(  ostream& outData, ostream& outLabel)
{
	for (int i=0; i<itemNum; i++)
	{
		for (int j=0; j<FEATURE_DIM; j++)
		{
			outData << data[i].feature[j] << "\t";
		}
		outLabel << data[i].label << endl;
	}
}

