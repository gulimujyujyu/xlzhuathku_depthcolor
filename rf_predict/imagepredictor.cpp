#include "imagepredictor.h"

////synthetic data
//int		R[] = {255,255,  0,  0, 75,139,255, 25,  0,128,255,255, 65, 46,216,255,238,  0,  0,189,112, 47,128,210};
//int		G[] = {  0,255,  0,255,  0,  0, 69, 25,100,  0, 20,160,105,139,191,182,232,191,255,183,128, 79,128,105};
//int		B[] = {  0,  0,255,  0,130,  0,  0,112,  0,128,147,122,225, 87,216,193,170,255,127,107,144, 79,128, 30};
//int LABEL[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23};
////int LABEL[] = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};

//real data
int		R[] = {255,255,  0,  0,  0,255,255};
int		G[] = {  0,  0,  0,255,255,255,255};
int		B[] = {  0,255,255,  0,255,255,  0};
int LABEL[] = {  0,  1,  2,  3,  4,  5,  6};
//int LABEL[] = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};

ImagePredictor::ImagePredictor(void)
{
	init();
}

ImagePredictor::~ImagePredictor(void)
{
	if (this->data)
	{
		cvReleaseImage(&(this->data));
	}
	if (this->label)
	{
		cvReleaseImage(&(this->label));
	}
}

void ImagePredictor::init()
{
	this->data = NULL;
	this->label = NULL;
	createHash();
}

void ImagePredictor::createHash()
{
	for( int i=0; i<24; i++) {
		hashRGB[i] = R[i]*1000000 + G[i]*1000 + B[i];
	}
}

bool ImagePredictor::readData(const char* filename)
{
	if (this->data)
		cvReleaseImage(&(this->data));
	this->data = cvLoadImage(filename);
	if (this->data)
		return false;
	return true;
}

bool ImagePredictor::readLabel(const char* filename)
{
	if(this->label)
		cvReleaseImage(&(this->label));
	this->label = cvLoadImage(filename);
	if(this->label)
		return false;
	return true;
}

bool ImagePredictor::readForest(const char* filename)
{
	ifstream in;
	in.open(filename, ios::in);

	if (!(in.good()))
		return false;
	this->forest.read(in);
	in.close();
	return true;
}

bool ImagePredictor::saveData(const char *filename)
{
	if(this->data)
		cvSaveImage(filename, this->data);
	else
		return false;
	return true;
}

bool ImagePredictor::saveLabel(const char *filename)
{
	if(this->label)
		cvSaveImage(filename, this->label);
	else
		return false;
	return true;
	return true;
}

bool ImagePredictor::readParam(const char *filename)
{
	ifstream in;
	in.open(filename, ios::in);

	if (!(in.good()))
		return false;

	for ( int i=0; i<SEEDS_ARRAY_SIZE; i++)
	{
		in >> this->offset[i][0]
			>> this->offset[i][1];
	}
	in.close();
	return true;
}

bool ImagePredictor::writeParam(const char* filename)
{
	ofstream out;
	out.open(filename, ios::out);

	if (!(out.good()))
		return false;

	for ( int i=0; i<SEEDS_ARRAY_SIZE; i++)
	{
		out << this->offset[i][0] << '\t'
			<< this->offset[i][1] << endl;
	}
	out.close();
	return false;
}

bool ImagePredictor::writeForest(const char* filename)
{
	ofstream out;
	out.open(filename, ios::out);

	if(!(out.good())) 
		return false;
	this->forest.write(out);
	out.close();
	return true;
}

void ImagePredictor::setForestParam(int tNum, int K)
{
	this->forest.set(tNum,K);
}

bool ImagePredictor::predictData()
{
	if ( this->forest.isEmpty())
		return false;
	if ( !(this->data))
		return false;
	if ( this->label)
		cvReleaseImage(&(this->label));
	
	this->label = cvCloneImage(this->data);

	int lb;
	int jj;
	for( int xx = 0; xx < width; xx ++) 
		for ( int yy =0; yy<height; yy ++) {
			//predict
			lb = predictOnePixel(xx,yy);
			//mapping
			for(jj=0;jj<24;jj++) 
				if(LABEL[jj]==lb)
					break;
			if(jj >= 24) {
				((uchar*)(this->label->imageData + this->label->widthStep*yy))[xx*3] = 0;
				((uchar*)(this->label->imageData + this->label->widthStep*yy))[xx*3+1] = 0;
				((uchar*)(this->label->imageData + this->label->widthStep*yy))[xx*3+2] = 0;
			} else {
				((uchar*)(this->label->imageData + this->label->widthStep*yy))[xx*3] = B[jj];
				((uchar*)(this->label->imageData + this->label->widthStep*yy))[xx*3+1] = G[jj];
				((uchar*)(this->label->imageData + this->label->widthStep*yy))[xx*3+2] = R[jj];
			}
		}
	return true;
}

int ImagePredictor::predictOnePixel(int xx, int yy)
{
	int idx = 0;
	int treeNo;
	int attr = 0;
	float splitA = 0;
	float sumA = 0;
	float p1, p2, p3;
	int u1, v1;
	int maxLabel = -1;
	float maxValue = -1;
	vector<float> rslt(CLASS_NUM, 0);
	Item px;

	//extract feature
	//get element: depth;
	p1 = (float)(((uchar*)(data->imageData + data->widthStep*yy))[xx*3]);
	if ( p1 < 0.5)
		return -1;
	p1 = 255-p1;
	for ( int i=0; i<SEEDS_ARRAY_SIZE; ) {
		//check
		u1 = xx + offset[i][0];
		v1 = yy + offset[i][1];
		if ( u1 < 0 || u1 >= width || v1 < 0 || v1 >= height) 
			p2 = MAX_DEPTHVALUE;
		else 
			p2 = (float)(((uchar*)(data->imageData + data->widthStep*(v1)))[(u1)*3]);
		i++;

		u1 = xx + offset[i][0];
		v1 = yy + offset[i][1];
		if ( u1 < 0 || u1 >= width || v1 < 0 || v1 >= height)
			p3 = MAX_DEPTHVALUE;
		else
			p3 = (float)(((uchar*)(data->imageData + data->widthStep*(v1)))[(u1)*3]);
		i++;

		p2 = p2<0.5? MAX_DEPTHVALUE: (255-p2);
		p3 = p3<0.5? MAX_DEPTHVALUE: (255-p3);
		px.feature[(i-1)/2] = p2 - p3;			
	}
	//prediction
	rslt = this->forest.predict(px);
	for( int j=0; j<rslt.size(); j++) {
		if( maxValue < rslt[j]) {
			maxValue = rslt[j];
			maxLabel = j;
		}
	}
	return maxLabel;
}

void ImagePredictor::setParameter(int w, int h, int rw, int rh)
{
	this->width = w;
	this->height = h;
	this->rectWidth = rw;
	this->rectHeight = rh;
}