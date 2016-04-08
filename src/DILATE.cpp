#include "DILATE.hpp"



//=================CONSTRUCTOR DESTRUCTOR========================


DILATE::DILATE(Data *data) : AbstractFilter(data)
{
	dilateSize = Settings::loadFromFile("DILATE_SIZE");
	dilateType = Settings::loadFromFile("DILATE_TYPE");

	element = getStructuringElement(dilateType,
		Size(dilateSize + 1, dilateSize + 1));

	createTrackbar("DILATE_SIZE", "Settings", &dilateSize, 100, setSize, this);
	createTrackbar("DILATE_TYPE", "Settings", &dilateType, 2, setType, this);
}


DILATE::~DILATE()
{
}


//===============================================================


void DILATE::filter()
{
	dilate(*ptrData->getLastImage(), *out, element);
	ptrData->addImage(out);
}


void DILATE::saveSettings()
{
	Settings::saveToFile("DILATE_SIZE", dilateSize);
	Settings::saveToFile("DILATE_TYPE", dilateType);
}



//==============TRACKBAR CALLBACKFUNCTIONS==================


void DILATE::setSize(int value, void * userData)
{
	DILATE *temp = (DILATE *)userData;
	temp->dilateSize = value;
	temp->element = getStructuringElement(temp->dilateType,
		Size(temp->dilateSize + 1, temp->dilateSize + 1));
}


void DILATE::setType(int value, void * userData)
{
	DILATE *temp = (DILATE *)userData;
	temp->dilateType = value;
	temp->element = getStructuringElement(temp->dilateType,
		Size(temp->dilateSize + 1, temp->dilateSize + 1));
}

