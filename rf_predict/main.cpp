#include"../rf_train./forest_id3.h"
#include "imagepredictor.h"
#include<fstream>
using namespace std;

#define TREE_DEPTH 20

int main()
{
	//sliding window
	int w = 224;
	int h = 220;
	int rw = 64;
	int rh = 64;

	//debug
	//Random Forest
	char treeFilename[] = "..\\rf_train\\data\\2011_28_26_21_14_10_943.tree";
	char outTreeFilename[] = "..\\rf_train\\data\\2011_28_26_21_14_10_943.treeout";
	//param
	char paramFilename[] = "..\\rf_train\\data\\2011_28_26_21_14_10_943.param";
	char paramOutFilename[] = "..\\rf_train\\data\\2011_28_26_21_14_10_943.out.param";
	//image
	char dataFilename[] = "..\\rf_train\\data\\453depth.png";
	char dataOutFilename[] = "..\\rf_train\\data\\453depth.out.png";
	//LABEL
	char labelFilename[] = "..\\rf_train\\data\\453color.png";
	char labelOutFilename[] = "..\\rf_train\\data\\453color.out.png";

	//xlzhulab
	////Random Forest
	//char treeFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/2011_28_26_21_14_10_943.tree";
	//char outTreeFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/2011_28_26_21_14_10_943.treeout";
	////param
	//char paramFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/2011_28_26_21_14_10_943.param";
	//char paramOutFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/2011_28_26_21_14_10_943.param";
	////image
	//char dataFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/13depth.png";
	//char dataOutFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/13depth_out.png";
	////LABEL
	//char labelFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/13color.png";
	//char labelOutFilename[] = "E:\\DATA\\[CDC4CV11]\\RealTest\\2011_28_06_21_14_10_943\\done/13color_out.png";

	ifstream inTree;
	ofstream outTree;
	
	inTree.open( treeFilename, ios::in);
	outTree.open( outTreeFilename, ios::out);
	
	
	
	//xlzhumac
	////Random Forest
	//char treeFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000.tree";
	//char outTreeFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000.treeout";
	////param
	//char paramFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000.param";
	//char paramOutFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000_out.param";
	//ifstream inTree;
	//ofstream outTree;

	//inTree.open( treeFilename, ios::in);
	//outTree.open( outTreeFilename, ios::out);
	//
	////image
	//char dataFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000004_depth.png";
	//char dataOutFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000004_depth_out.png";

	////LABEL
	//char labelFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000004_color.png";
	//char labelOutFilename[] = "C:\\Users\\xiaolongzhu\\Research\\PROJECTs\\[CDC4CV]HandTracking\\DATA\\ForRealData\\333\\train/000004_color_out.png";

	

	


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

