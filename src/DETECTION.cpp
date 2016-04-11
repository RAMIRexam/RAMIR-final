#include "DETECTION.hpp"



//=====================CONSTRUCTOR DESTRUCTOR======================

DETECTION::DETECTION(Data * data) : AbstractDetection(data)
{
}


DETECTION::~DETECTION()
{
}


//=================================================================


void DETECTION::detect()
{
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;

	vector<Blob *> *blobVector = new vector<Blob *>();

	Mat temp, hist;
	ptrData->getLastImage()->copyTo(temp);

	findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	//====================================================
	int hbins = 30, sbins = 32;
	int histSize[] = { hbins, sbins };
	float hranges[] = { 0, 180 };
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	int channels[] = { 0, 1 };
	//=====================================================

	ptrData->getLastImage()->copyTo(*out);
	cvtColor(*out, *out, CV_GRAY2BGR, 3);

	//Calculate blob data
	for (vector<Point> cont : contours) 
	{

		//calculates a bounding rectangle around the contour
		Rect rect = boundingRect(cont);


		//Creates a ROI on same spot as the rectangle
		Mat blobROI(ptrData->getImage()->clone(), rect);


		//Calculates the histogram for the ROI, NOT USED EVER!!!!
		calcHist(&blobROI, 1, channels, Mat(), hist, 2, histSize, ranges);
		normalize(hist, hist, 0, 1, NORM_MINMAX, -1, Mat());


		//Find the centroid at the contour
		Moments m = moments(cont, false);
		Point2f cent = Point2f(m.m10 / m.m00, m.m01 / m.m00);
		
		//Draw a ellipse at centroid of blob
		ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 0, 255), 2); 

		//Add to frameBlobVector in data
		Blob *b = new Blob(hist, rect, blobROI, cent);
		b->setArea(m.m00);
		blobVector->push_back(b);
		
	}
	ptrData->setFrameBlobVector(blobVector);
	ptrData->addImage(out);
}


void DETECTION::saveSettings()
{
}