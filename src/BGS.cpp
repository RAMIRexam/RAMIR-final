#include "BGS.hpp"



BGS::BGS(Data * data) :AbstractSegment(data)
{
	firstRun = true;
}


BGS::~BGS()
{
}

void BGS::segment()
{
	if (firstRun)
	{
		model = *ptrData->getLastImage();
		firstRun = false;
	}

}

void BGS::saveSettings()
{
}
