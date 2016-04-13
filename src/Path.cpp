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
	ptrLastBlob = NULL;
	staSOL = LINESIDE_NOTDEFINED;				//will be determined in the counting class

	blobs->push_back(blob);
	ptrLastBlob = blob;

	setCounted(false);

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
	else {
		ptrLastBlob = blob;
		remainingLife = nLife;
	}
}

vector<Blob*>* Path::getBlobVector()
{
	return blobs;
}


Blob * Path::getLastBlob()
{
	return ptrLastBlob;
}

void Path::setLife(int life)
{
	nLife = life;
	remainingLife = nLife;
}

int Path::getDuration()
{
	return blobs->size();
}

bool Path::isAlive()
{
	return remainingLife > 0;
}

void Path::setHeading(Point2f heading)
{
	this->heading = heading;
}

Point Path::getHeading()
{
	return heading;
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



