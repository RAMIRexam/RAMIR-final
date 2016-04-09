#include "FIT_OBJECT.hpp"



FIT_OBJECT::FIT_OBJECT(Data * data) : AbstractDetection(data)
{
}

FIT_OBJECT::~FIT_OBJECT()
{
}




void FIT_OBJECT::filter()
{
	vector<Blob *> *blobs = ptrData->getFrameBlobVector();
	
	for (Blob *b : *blobs)
	{
		Mat temp(*ptrData->getLastImage(), b->getRect());
	}
}


void FIT_OBJECT::saveSettings()
{
}
