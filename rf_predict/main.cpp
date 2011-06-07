#include"../rf_train./forest_id3.h"
#include "imagepredictor.h"
#include<fstream>
using namespace std;

#define TREE_DEPTH 20

int main()
{
	//Random Forest
	char treeFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000.treein";
	char outTreeFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000.treeout";
	ifstream inTree;
	ofstream outTree;

	inTree.open( treeFilename, ios::in);
	outTree.open( outTreeFilename, ios::out);
	
	//image
	char dataFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000_color_in.png";
	char dataOutFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000_color_out.png";

	//LABEL
	char labelFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000_label_in.png";
	char labelOutFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000_label_out.png";

	//param
	char paramFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000_in.param";
	char paramOutFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\TOY1/000000_out.param";

	//sliding window
	int w = 512;
	int h = 512;
	int rw = 64;
	int rh = 64;


	ImagePredictor ip;
	ip.setForestParam( 5, CLASS_NUM);
	ip.setParameter(w,h,rw,rh);
	//ip.readForest(treeFilename);
	//ip.writeForest(outTreeFilename);

	//ip.readData(dataFilename);
	//ip.saveData(dataOutFilename);

	
	//ip.writeParam(paramOutFilename);

	//ip.readLabel(labelFilename);
	//ip.saveLabel(labelOutFilename);

	ip.readForest(treeFilename);
	ip.readData(dataFilename);
	ip.readParam(paramFilename);
	ip.predictData();
	ip.saveLabel(labelOutFilename);
	return 0;
}

