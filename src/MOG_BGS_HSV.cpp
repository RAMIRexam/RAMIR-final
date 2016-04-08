#include "MOG_BGS_HSV.hpp"



MOG_BGS_HSV::MOG_BGS_HSV(Data * data) : AbstractSegment(data)
{
	shadows = false;

	//Load settings if they exist
	history = Settings::loadFromFile("MOG_BGS_HSV_History");
	threshold = Settings::loadFromFile("MOG_BGS_HSV_Threshold");

	pMOG = createBackgroundSubtractorMOG2(history, threshold, shadows);

	//Create trackbar
	createTrackbar("MOG_BGS_HSV_History", "Settings", &history, 2000, setHistory, this);
	createTrackbar("MOG_BGS_HSV_Threshold", "Settings", &threshold, 500, setThreshold, this);
}


MOG_BGS_HSV::~MOG_BGS_HSV()
{
	pMOG.release();
}

void MOG_BGS_HSV::segment()
{
	Mat temp;
	cvtColor(*ptrData->getLastImage(), temp, CV_BGR2HSV);
	pMOG->apply(temp, *out);
	ptrData->addImage(out);
}

void MOG_BGS_HSV::saveSettings()
{
	Settings::saveToFile("MOG_BGS_HSV_History", history);
	Settings::saveToFile("MOG_BGS_HSV_Threshold", threshold);
}



//===============TRACKBAR CALLBACKFUNCTIONS=========================


void MOG_BGS_HSV::setHistory(int value, void * userdata)
{
	MOG_BGS_HSV *temp = (MOG_BGS_HSV *)userdata;
	temp->pMOG.release();
	temp->history = value;
	temp->pMOG = createBackgroundSubtractorMOG2(temp->history + 1, (double)temp->threshold / 10.0, temp->shadows);
}


void MOG_BGS_HSV::setThreshold(int value, void * userdata)
{
	MOG_BGS_HSV *temp = (MOG_BGS_HSV *)userdata;
	temp->pMOG.release();
	temp->threshold = value;
	temp->pMOG = createBackgroundSubtractorMOG2(temp->history, (double)(temp->threshold + 1) / 10.0, temp->shadows);
}