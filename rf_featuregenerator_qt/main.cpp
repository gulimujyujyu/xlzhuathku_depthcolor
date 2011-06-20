#include <QtCore/QCoreApplication>
#include <iostream>
#include <string>
#include <QString>
#include <QDebug>
#include "featuregenerator.h"
#include "filevalidator.h"
#include "time.h"
using namespace std;

int offx[SEEDS_ARRAY_SIZE];
int offy[SEEDS_ARRAY_SIZE];

void generateSeeds()
{
	for ( int i=0; i < SEEDS_ARRAY_SIZE; i++) {
		offx[i] = rand();
		offy[i] = rand();
	}
}

int main(int argc, char *argv[])
{
	//char dirr[] = "F:\\xlzhu\\DATAs\\[CDC4CV]HandTracking\\000\\";
	char dirr[] = "E:\\DATA\\[CDC4CV11]\\DATASET1\\Synthetic1\\018";
	char re[] = "(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)depth.png";
 	
	int w = 512;
	int h = 512;
	int rw = 64;
	int rh = 64;

	//get a file
	FileValidator fv(re, dirr);
	//qDebug() << fv.findFileInDir() << endl;

	string outFilename = "018.txt";
	string outParamFilename = "018.param";
	string outLabelFilename = "018.label";

	srand(time(NULL));
	generateSeeds();

	FeatureGenerator a;
	a.setSeeds(offx, offy);
	a.setParameter(w,h,rw,rh);
	a.createHash();
	if (!(a.setOutputFilename(outFilename.c_str(),outParamFilename.c_str(), 0)))
	{
		printf("Error occurred in writing to %s, %s", outFilename.c_str(),outParamFilename.c_str());
		return -1;
	}
	if (!(a.setOutputFilenameLabel(outLabelFilename.c_str(), 0)))
	{
		printf("Error occurred in writing to %s", outLabelFilename.c_str());
		return -1;
	}
	
	//generate features
	int lat = 0;
	int lon = 0;
	QString depthFilename;
	QString colorFilename;
	QString depthimg;
	QByteArray di;
	QString colorimg;
	QByteArray ci;

	for (lat = -90; lat <= 90; lat += 20) {
		for ( lon = 0; lon < 360; lon += 20) {
			printf("(%d, %d).\n", lat, lon);

			depthFilename = QString::number(lat) + QString("_") + QString::number(lon) + QString("_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)depth.png");
			colorFilename = QString::number(lat) + QString("_") + QString::number(lon) + QString("(_\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)color.png");
			fv.setRegExpStr(depthFilename);
			depthimg = fv.findFileInDir();
			qDebug() << depthimg << endl;

			di = depthimg.toLocal8Bit();
			if (!(a.read(di.data())))
			{
				printf("Error occured in reading %s", di.data());
				return -1;
			}

			fv.setRegExpStr(colorFilename);
			colorimg = fv.findFileInDir();
			qDebug() << colorimg << endl;

			ci = colorimg.toLocal8Bit();
			if (!(a.readLabel(ci.data())))
			{
				printf("Error occured in reading %s", ci.data());
				return -1;
			}
			a.generateFeatures();
			a.generateLabels();
		}
	}
	/*
	QString depthFilename = QString::number(lat) + QString("_") + QString::number(lon) + QString("_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)depth.png");
	QString colorFilename = QString::number(lat) + QString("_") + QString::number(lon) + QString("(_\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)_(\\d+)color.png");

	fv.setRegExpStr(depthFilename);
	QString depthimg = fv.findFileInDir();

	QByteArray di = depthimg.toLocal8Bit();
	if (!(a.read(di.data())))
	{
		printf("Error occured in reading %s", di.data());
		return -1;
	}

	fv.setRegExpStr(colorFilename);
	QString colorimg = fv.findFileInDir();

	QByteArray ci = colorimg.toLocal8Bit();
	if (!(a.readLabel(ci.data())))
	{
		printf("Error occured in reading %s", ci.data());
		return -1;
	}
	a.generateFeatures();
	a.generateLabels();
	*/
	printf("Finished.\n");

	QCoreApplication app(argc, argv);

	return app.exec();
}
