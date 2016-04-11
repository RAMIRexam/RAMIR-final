#include "AREA_DETECT.hpp"



AREA_DETECT::AREA_DETECT(Data * data) : AbstractDetection(data)
{
	areaLimit_1P = Settings::loadFromFile("AREA_DETECT_LIMIT_1P");
	areaLimit_2P = Settings::loadFromFile("AREA_DETECT_LIMIT_2P");
	areaLimit_3P = Settings::loadFromFile("AREA_DETECT_LIMIT_3P");

	createTrackbar("AREA_DETECT_LIMIT_1P", "Settings", &areaLimit_1P, 40000, setAreaLimit_1P, this);
	createTrackbar("AREA_DETECT_LIMIT_2P", "Settings", &areaLimit_2P, 40000, setAreaLimit_2P, this);
	createTrackbar("AREA_DETECT_LIMIT_3P", "Settings", &areaLimit_3P, 40000, setAreaLimit_3P, this);
}


AREA_DETECT::~AREA_DETECT()
{
}

void AREA_DETECT::detect()
{
	Rect rect;
	Point2f cent;
	Blob *b;
	vector<Blob *> *blobVector = ptrData->getFrameBlobVector();

	ptrData->getLastImage()->copyTo(*out);

	for (int i = 0; i < blobVector->size(); i++)
	{
		b = blobVector->at(i);
		rect = b->getRect();
		cent = b->getCentroid();

		if (b->getArea() > areaLimit_3P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 0, 255), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(255, 0, 0), 2);	//TEST CODE!
		}
		else if (b->getArea() > areaLimit_2P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(255, 0, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 255, 0), 2);	//TEST CODE!
		}
		else if (b->getArea() > areaLimit_1P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 255, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 0, 255), 2);	//TEST CODE!
		}
		else
		{
			delete b;
			blobVector->erase(blobVector->begin() + i);
		}
	}
	ptrData->addImage(out); //UNNECESSARY? TEST CODE!
}

void AREA_DETECT::saveSettings()
{
	Settings::saveToFile("AREA_DETECT_LIMIT_1P", areaLimit_1P);
	Settings::saveToFile("AREA_DETECT_LIMIT_2P", areaLimit_2P);
	Settings::saveToFile("AREA_DETECT_LIMIT_3P", areaLimit_3P);
}



//===============TRACKBAR CALLBACKFUNCTIONS=========================


void AREA_DETECT::setAreaLimit_1P(int value, void * userData)
{
	AREA_DETECT *temp = (AREA_DETECT *)userData;
	temp->areaLimit_1P = value;
}

void AREA_DETECT::setAreaLimit_2P(int value, void * userData)
{
	AREA_DETECT *temp = (AREA_DETECT *)userData;
	temp->areaLimit_2P = value;
}

void AREA_DETECT::setAreaLimit_3P(int value, void * userData)
{
	AREA_DETECT *temp = (AREA_DETECT *)userData;
	temp->areaLimit_3P = value;
}