#include "MOG_BGS.hpp"


//=================CONSTRUCTOR DESTRUCTOR========================

MOG_BGS::MOG_BGS(Data * data) : AbstractSegment(data)
{	
	shadows = false;

	//Load settings if they exist
	history = Settings::loadFromFile("MOG_BGS_History");
	threshold = Settings::loadFromFile("MOG_BGS_Threshold");

	pMOG = createBackgroundSubtractorMOG2(history, threshold, shadows);

	//Create trackbar
	createTrackbar("MOG_BGS_History", "Settings", &history, 2000, setHistory, this);
	createTrackbar("MOG_BGS_Threshold", "Settings", &threshold, 500, setThreshold, this);
}


MOG_BGS::~MOG_BGS()
{
	pMOG.release();
}


//===============================================================


/*
	Preform a segmentation to an image
*/
void MOG_BGS::segment()
{
	pMOG->apply(*ptrData->getLastImage(), *out);
	ptrData->addImage(out);
}


/*
	Save the settings when promted
*/
void MOG_BGS::saveSettings()
{
	Settings::saveToFile("MOG_BGS_History", history);
	Settings::saveToFile("MOG_BGS_Threshold", threshold);
}







//===============TRACKBAR CALLBACKFUNCTIONS=========================


void MOG_BGS::setHistory(int value, void * userdata)
{
	MOG_BGS *temp = (MOG_BGS *)userdata;
	temp->pMOG.release();
	temp->history = value;
	temp->pMOG = createBackgroundSubtractorMOG2(temp->history+1, (double)temp->threshold / 10.0, temp->shadows);
}


void MOG_BGS::setThreshold(int value, void * userdata)
{
	MOG_BGS *temp = (MOG_BGS *)userdata;
	temp->pMOG.release();
	temp->threshold = value;
	temp->pMOG = createBackgroundSubtractorMOG2(temp->history, (double)(temp->threshold+1) / 10.0, temp->shadows);
}


