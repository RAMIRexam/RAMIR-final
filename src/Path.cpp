/*
A path-object is the path taken by a pedestrian in the video.
*/

#include "Path.hpp"


//==================CONSTRUCTOR DESTRUCTOR========================

Path::Path(Blob * blob, int pathLife)
{
	nLife = pathLife;
	remainingLife = nLife;

	blobs = new vector<Blob *>();

	staSOL = LINESIDE_NOTDEFINED;				//used in COUNTER_CC, will be set first iteration.
	curSOL = LINESIDE_NOTDEFINED;				//will be updated each iteration in the counting class

	blobs->push_back(blob);
	ptrLastBlob = blob;

	isCounted = false;

}


Path::~Path()
{
	for (unsigned int i = 0; i < blobs->size(); i++)
	{
		delete blobs->at(i);
	}
	delete blobs;
}


//================================================================


void Path::addBlob(Blob * blob)
{
	blobs->push_back(blob);
	if (blob->isEmpty()) {
		--remainingLife;
	}
	else if (blob->isGhost())
	{
		ptrLastBlob = blob;
		--remainingLife;
	}
	else {
		ptrLastBlob = blob;
		remainingLife = nLife;
	}
}






Blob * Path::getBlob(int index)
{
	return blobs->at(index);
}


Blob * Path::getLastBlob()
{
	return ptrLastBlob;
}






int Path::getNrBlobs()
{
	return blobs->size();
}


vector<Blob*>* Path::getBlobVector()
{
	return blobs;
}










void Path::setLife(int life)
{
	nLife = life;
	remainingLife = nLife;
}


bool Path::isAlive()
{
	return remainingLife > 0;
}








void Path::addHeading(Point2f heading)
{
	this->headingSum += heading;
}

Point2f Path::getHeading()
{
	return (headingSum / (int)blobs->size());
}






void Path::addArea(int area)
{
	this->areaSum += area;
}


int Path::getMeanArea()
{
	return (areaSum / blobs->size());
}













bool Path::isCountedCheck() {
	return isCounted;
}

void Path::setCounted(bool counted) {
	isCounted = counted;
}














//For TRACKING_CC

//set start Side Of Line
void Path::set_staSOL(int lineSide) {
	if (lineSide == LINESIDE_LEFT) {
		staSOL = LINESIDE_LEFT;
		curSOL = LINESIDE_LEFT;
	}
	else {
		assert(lineSide == LINESIDE_RIGHT);
		staSOL = LINESIDE_RIGHT;
		curSOL = LINESIDE_RIGHT;
	}
}

//get start side of line
int Path::get_staSOL() {
	return staSOL;
}

//set current side of line
void Path::set_curSOL(int lineSide) {
	assert(lineSide == LINESIDE_LEFT || lineSide == LINESIDE_RIGHT || lineSide == LINESIDE_NOTDEFINED);
	curSOL = lineSide;
}

//get current side of line
int Path::get_curSOL() {
	return curSOL;
}



