#include "item.h"
#include "id3tree.h"
#include <fstream>
#include <iostream>

int main()
{
	ifstream inData;
	ifstream inLabel;
	char dataFilename[] = "data/heart_data.txt";
	char labelFilename[] = "data/heart_labels.txt";
	inLabel.open( labelFilename, ifstream::in);
	inData.open(dataFilename, ifstream::in );
	if( !(inLabel.good())|| !(inData.good()))
	{
		printf("open failed.");
		return -1;
	}
	ItemSet trainSet( inData, inLabel, 270);
	ID3Tree tree(trainSet, 4, 10);
	//trainSet.write( cout, cout);
	tree.print(cout);

	cout << tree.test( trainSet) << endl;
	inLabel.close();
	inData.close();
	return 0;
}