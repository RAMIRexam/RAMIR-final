#include "ERODE.hpp"



//=================CONSTRUCTOR DESTRUCTOR========================


ERODE::ERODE(Data *data) : AbstractFilter(data)
{
	erodeSize = Settings::loadFromFile("ERODE_SIZE");
	erodeType = Settings::loadFromFile("ERODE_TYPE");

	element = getStructuringElement(erodeType,
		Size(erodeSize + 1, erodeSize + 1));

	createTrackbar("ERODE_SIZE", "Settings", &erodeSize, 100, setSize, this);
	createTrackbar("ERODE_TYPE", "Settings", &erodeType, 2, setType, this);
}


ERODE::~ERODE()
{
}


//===============================================================


void ERODE::filter()
{
	erode(*ptrData->getLastImage(), *out, element);
	ptrData->addImage(out);
}


void ERODE::saveSettings()
{
	Settings::saveToFile("ERODE_SIZE", erodeSize);
	Settings::saveToFile("ERODE_TYPE", erodeType);
}



//==============TRACKBAR CALLBACKFUNCTIONS==================


void ERODE::setSize(int value, void * userData)
{
	ERODE *temp = (ERODE *)userData;
	temp->erodeSize = value;
	temp->element = getStructuringElement(temp->erodeType,
		Size(temp->erodeSize + 1, temp->erodeSize + 1));
}


void ERODE::setType(int value, void * userData)
{
	ERODE *temp = (ERODE *)userData;
	temp->erodeType = value;
	temp->element = getStructuringElement(temp->erodeType,
		Size(temp->erodeSize + 1, temp->erodeSize + 1));
}

