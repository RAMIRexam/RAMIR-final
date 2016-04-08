#include "DETECTION.hpp"



//=====================CONSTRUCTOR DESTRUCTOR======================

DETECTION::DETECTION(Data * data) : AbstractDetection(data)
{
	areaLimit_1P = Settings::loadFromFile("DETECTION_AREA_LIMIT_1P");
	areaLimit_2P = Settings::loadFromFile("DETECTION_AREA_LIMIT_2P");
	areaLimit_3P = Settings::loadFromFile("DETECTION_AREA_LIMIT_3P");

	createTrackbar("DETECTION_AREA_LIMIT_1P", "Settings", &areaLimit_1P, 40000, setAreaLimit_1P, this);
	createTrackbar("DETECTION_AREA_LIMIT_2P", "Settings", &areaLimit_2P, 40000, setAreaLimit_2P, this);
	createTrackbar("DETECTION_AREA_LIMIT_3P", "Settings", &areaLimit_3P, 40000, setAreaLimit_3P, this);
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
		
		
		if (m.m00 > areaLimit_3P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 0, 255), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(255, 0, 0), 2);	//TEST CODE!
			blobVector->push_back(new Blob(hist, rect, blobROI, cent));
			blobVector->push_back(new Blob(hist, rect, blobROI, cent));
			blobVector->push_back(new Blob(hist, rect, blobROI, cent));
		}
		else if (m.m00 > areaLimit_2P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(255, 0, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 255, 0), 2);	//TEST CODE!
			blobVector->push_back(new Blob(hist, rect, blobROI, cent));
			blobVector->push_back(new Blob(hist, rect, blobROI, cent));
		}
		else if (m.m00 > areaLimit_1P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 255, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 0, 255), 2);	//TEST CODE!
			blobVector->push_back(new Blob(hist, rect, blobROI, cent));
		}

	}
	ptrData->setFrameBlobVector(blobVector);
	ptrData->addImage(out); //UNNECESSARY? TEST CODE!
}


void DETECTION::saveSettings()
{
	Settings::saveToFile("DETECTION_AREA_LIMIT_1P", areaLimit_1P);
	Settings::saveToFile("DETECTION_AREA_LIMIT_2P", areaLimit_2P);
	Settings::saveToFile("DETECTION_AREA_LIMIT_3P", areaLimit_3P);
}



//===============TRACKBAR CALLBACKFUNCTIONS=========================


void DETECTION::setAreaLimit_1P(int value, void * userData)
{
	DETECTION *temp = (DETECTION *)userData;
	temp->areaLimit_1P = value;
}

void DETECTION::setAreaLimit_2P(int value, void * userData)
{
	DETECTION *temp = (DETECTION *)userData;
	temp->areaLimit_2P = value;
}

void DETECTION::setAreaLimit_3P(int value, void * userData)
{
	DETECTION *temp = (DETECTION *)userData;
	temp->areaLimit_3P = value;
}
