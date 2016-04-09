#include "BGS.hpp"



BGS::BGS(Data * data) :AbstractSegment(data)
{
	firstRun = true;
	threshold = Settings::loadFromFile("BGS_Threshold");

	createTrackbar("BGS_THRESHOLD", "Settings", &threshold, 255, setThreshold, this);
}


BGS::~BGS()
{
}




void BGS::segment()
{
	if (firstRun)
	{
		ptrData->getLastImage()->copyTo(model);
		cvtColor(model, model, CV_BGR2GRAY);
		firstRun = false;
	}
	Mat temp;
	Mat frame;
	ptrData->getLastImage()->copyTo(frame);
	cvtColor(frame, frame, CV_BGR2GRAY);
	temp = abs(model - frame) > threshold; 
	temp.copyTo(*out);
	ptrData->addImage(out);
}




void BGS::saveSettings()
{
	Settings::saveToFile("BGS_Threshold", threshold);
}



//===============TRACKBAR CALLBACKFUNCTIONS=========================


void BGS::setThreshold(int value, void * userdata)
{
	BGS *temp = (BGS *)userdata;
	temp->threshold = value;
}
