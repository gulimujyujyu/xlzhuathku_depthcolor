#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QRegExp>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
using namespace cv;
using namespace std; 

void processVideo( QFileInfo &vi);
bool saveFrames( QFileInfo &vi, QString &folderName, QString np, QString fp);

int main(int argc, char *argv[])
{
	if ( argc > 2)
	{
		printf( "Not enough arguements. \n");
		return -1;
	}
	
	char *videoFileName = argv[1];
	QString dirStr = QString::fromLocal8Bit(videoFileName);
	QFileInfo videoInfo(dirStr);	

	processVideo(videoInfo);

	return 0;
}

void processVideo(QFileInfo &vi)
{
	//2011_28_06_21_14_10_943_969_639roicapture
	QRegExp re("(\\d+_\\d+_\\d+_\\d+_\\d+_\\d+_\\d+)_(\\d+)_(\\d+)roicapture");
	int pos = re.indexIn( vi.filePath());

	if (pos <= -1)
	{
		printf( "Regexp not match. %s", vi.filePath().toLocal8Bit().data());
		return;
	}
	QString timeStamp = re.cap(1);
	QString farPlane = re.cap(2);
	QString nearPlane = re.cap(3);

	//debug
	printf( "%s\n", timeStamp.toLocal8Bit().data());
	printf( "%s\n", farPlane.toLocal8Bit().data());
	printf( "%s\n", nearPlane.toLocal8Bit().data());
	printf( "%s\n", vi.path().toLocal8Bit().data());
	printf( "%s\n", vi.fileName().toLocal8Bit().data());

	//Step 1: mkdir
	QDir dirr = vi.dir();
	if ( !dirr.mkdir(timeStamp)) {
		printf( "Dir exists. %s\n", timeStamp.toLocal8Bit().data());
		return;
	}

	//Step 2: save every frame
	if ( !saveFrames(vi, timeStamp, farPlane, nearPlane))
	{
		printf( "Cannot save frames in saveFrames().\n");
	}
	
	
}

bool saveFrames(QFileInfo &vi, QString &folderName, QString np, QString fp)
{
	string fn = vi.filePath().toLocal8Bit().data();
	VideoCapture vc( fn);
	if(!vc.isOpened()) {
		printf( "Cannot open video file. %s\n", vi.filePath().toLocal8Bit().data());
		return false;
	}

	QDir dirr = vi.dir();
	if ( !dirr.cd(folderName))
	{
		printf( "Cannot enter %s.\n", folderName.toLocal8Bit().data());
		return false;
	}	
	QString videoFolderName = dirr.canonicalPath();
	printf( "%s\n", videoFolderName.toLocal8Bit().data());

	//write to prop file
	QString propFileName = dirr.canonicalPath() + QString('/') + QString("this.videoproperty");
	QFile propFile(propFileName);
	if ( !propFile.open(QIODevice::WriteOnly))
	{
		printf( "Cannot open prop file to write. %s\n", propFileName.toLocal8Bit().data());
	}
	QTextStream propOut( &propFile);
	propOut << np << endl
			<< fp << endl
			<< folderName << endl;
	

	int ii = 0;
	//write every frame
	while (1)
	{
		Mat frame;
		if( !vc.grab()) {
			break;
		}
		vc.retrieve( frame);
		ii++;
		
		int height = frame.rows;
		int width = frame.cols;
		
		Mat colorFrame;
		Rect colorRect( 0, 0, width/2, height);
		colorFrame = frame(colorRect);
		Mat depthFrame;
		Rect depthRect( width/2, 0, width/2, height);
		depthFrame = frame(depthRect);

		imshow("color", colorFrame);
		imshow("depth", depthFrame);
		
		QString colorFileName = dirr.canonicalPath() + QString('/') + QString::number(ii) + QString("color.png");
		string clfn = colorFileName.toLocal8Bit().data();
		QString depthFileName = dirr.canonicalPath() + QString('/') + QString::number(ii) + QString("depth.png");
		string dpfn = depthFileName.toLocal8Bit().data();
		imwrite(clfn, colorFrame);
		imwrite(dpfn, depthFrame);
		if (waitKey(30) >= 0)
		{
			break;
		}	
	}
	propOut << ii << endl;
	propFile.close();
	return true;
}