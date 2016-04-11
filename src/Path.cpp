/*
A path-object is the path taken by a pedestrian in the video.
*/

#include "Path.hpp"


//==================CONSTRUCTOR DESTRUCTOR========================


Path::Path()
{
	nLife = 3;
	remainingLife = nLife;

	blobs = new vector<Blob *>();
	ptrLastBlob = NULL;

	staSOL = LINESIDE_NOTDEFINED;		//use other constructor in TRACKER_CC

}

Path::Path(int lineSide, )
{
	nLife = 3;
	remainingLife = nLife;

	blobs = new vector<Blob *>();
	ptrLastBlob = NULL;


	// Start side of entry/exit-line
	/******************************************/
	if (lineSide == LEFTSIDE_OFLINE) {
		staSOL = LEFTSIDE_OFLINE;
		curSOL = LEFTSIDE_OFLINE;
	}
	else {
		assert(lineSide == RIGHTSIDE_OFLINE);
		staSOL = RIGHTSIDE_OFLINE;
		curSOL = RIGHTSIDE_OFLINE;
	}
	/******************************************/
}





Path::Path(Blob * blob)
{
	nLife = 10;
	remainingLife = nLife;

	blobs = new vector<Blob *>();
	blobs->push_back(blob);
	ptrLastBlob = blob;
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



