#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

#define WIDTH 512
#define HEIGHT 512

char i2f_imgFilename[] = "data/000000_color.png";
char i2f_floatFilename[] = "data/000000_color.float";

char f2i_imgFilename[] = "";
char f2i_floatFilename[] = "";

void img2float()
{
	IplImage *pImg;
	FILE *pFile;
	int xx,yy;
	float tmp;

	pImg = cvLoadImage(i2f_imgFilename, 1);
	pFile = fopen(i2f_floatFilename, "w");
	for( yy=0; yy<HEIGHT; yy++) {
		for(xx=0; xx<WIDTH; xx++) {
			tmp = (float)(((uchar*)(pImg->imageData + pImg->widthStep*yy))[xx*3]);
			fprintf( pFile, "%f ", tmp);
		}
		fprintf( pFile, "\n");
	}
}

void float2img()
{
	//TODOcvSaveImage(imgFilename);
}

int main()
{
	img2float();
	return 0;
}