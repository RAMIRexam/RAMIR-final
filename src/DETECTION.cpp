#include "DETECTION.hpp"



//=====================CONSTRUCTOR DESTRUCTOR======================

DETECTION::DETECTION(Data * data) : AbstractDetection(data)
{
	areaLimit_1P = Settings::loadFromFile("DETECTION_AREA_LIMIT_1P");
	areaLimit_2P = Settings::loadFromFile("DETECTION_AREA_LIMIT_2P");
	areaLimit_3P = Settings::loadFromFile("DETECTION_AREA_LIMIT_3P");
	areaLimit_4P = Settings::loadFromFile("DETECTION_AREA_LIMIT_4P");
	areaLimit_5P = Settings::loadFromFile("DETECTION_AREA_LIMIT_5P");

	createTrackbar("DETECTION_AREA_LIMIT_1P", "Settings", &areaLimit_1P, 80000, setAreaLimit_1P, this);
	createTrackbar("DETECTION_AREA_LIMIT_2P", "Settings", &areaLimit_2P, 80000, setAreaLimit_2P, this);
	createTrackbar("DETECTION_AREA_LIMIT_3P", "Settings", &areaLimit_3P, 80000, setAreaLimit_3P, this);
	createTrackbar("DETECTION_AREA_LIMIT_4P", "Settings", &areaLimit_4P, 80000, setAreaLimit_4P, this);
	createTrackbar("DETECTION_AREA_LIMIT_5P", "Settings", &areaLimit_5P, 80000, setAreaLimit_5P, this);
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

	Mat temp;
	ptrData->getLastImage()->copyTo(temp);

	findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	ptrData->getLastImage()->copyTo(*out);
	cvtColor(*out, *out, CV_GRAY2BGR, 3);

	//Calculate blob data
	for (vector<Point> cont : contours)
	{

		//calculates a bounding rectangle around the contour
		Rect rect = boundingRect(cont);


		//Creates a ROI on same spot as the rectangle
		Mat blobROI(ptrData->getImage()->clone(), rect);


		//Find the centroid at the contour
		Moments m = moments(cont, false);
		Point2f cent = Point(m.m10 / m.m00, m.m01 / m.m00);


		if (m.m00 > areaLimit_5P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(166, 0, 166), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(166, 0, 166), 2);	//TEST CODE!
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m.m00 > areaLimit_4P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 166, 166), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 166, 166), 2);	//TEST CODE!
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m.m00 > areaLimit_3P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(255, 0, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(255, 0, 0), 2);	//TEST CODE!
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m.m00 > areaLimit_2P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 255, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 255, 0), 2);	//TEST CODE!
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m.m00 > areaLimit_1P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 0, 255), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 0, 255), 2);	//TEST CODE!
			blobVector->push_back(new Blob(cent, rect, blobROI));
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
	Settings::saveToFile("DETECTION_AREA_LIMIT_4P", areaLimit_4P);
	Settings::saveToFile("DETECTION_AREA_LIMIT_5P", areaLimit_5P);
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

void DETECTION::setAreaLimit_4P(int value, void * userData)
{
	DETECTION *temp = (DETECTION *)userData;
	temp->areaLimit_4P = value;
}

void DETECTION::setAreaLimit_5P(int value, void * userData)
{
	DETECTION *temp = (DETECTION *)userData;
	temp->areaLimit_5P = value;
}




//====================================================
/*int hbins = 30, sbins = 32;
int histSize[] = { hbins, sbins };
float hranges[] = { 0, 180 };
float sranges[] = { 0, 256 };
const float* ranges[] = { hranges, sranges };
int channels[] = { 0, 1 };*/
//=====================================================
//Calculates the histogram for the ROI, NOT USED EVER!!!!
/*calcHist(&blobROI, 1, channels, Mat(), hist, 2, histSize, ranges);
normalize(hist, hist, 0, 1, NORM_MINMAX, -1, Mat());*/