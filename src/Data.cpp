#include "Data.hpp"


//===============CONSTRUCTOR DESTRUCTOR==================


Data::Data()
{
	nImageCnt = 0;

	frameBlobs = nullptr;
	images = new vector<Mat *>();
	paths = new vector<Path *>();
}


Data::~Data()
{
	for (unsigned int i = 0; i < images->size(); i++)
	{
		images->at(i);
	}
	delete images;

	for (unsigned int i = 0; i < paths->size(); i++)
	{
		delete paths->at(i);
	}
	delete paths;

	for (unsigned int i = 0; i < frameBlobs->size(); i++)
	{
		delete frameBlobs->at(i);
	}
	delete frameBlobs;
}


//========================================================

/*
	A scene is the trackerarea. It is partly used to determine which side
	of the eeline (entry exit line) a blob currently is on.
*/
void Data::setScene(Scene* s) {
	scene = s;
}

Scene* Data::getScene() {
	assert(scene != NULL);
	return scene;
}



void Data::addImage(Mat * img)
{
	images->push_back(img);
}


Mat * Data::getImage(int index)
{
	return images->at(index);
}


Mat * Data::getLastImage()
{
	return images->at(images->size() - 1);
}


void Data::clearImages()
{
	for (unsigned int i = 0; i < images->size(); i++)
	{
		images->at(i)->release();
	}

	images->clear();
}


//======================================================

void Data::addPath(Path * path)
{
	paths->push_back(path);
}

vector<Path*>* Data::getPathVector()
{
	return paths;
}


//===============================================
void Data::setFrameBlobVector(vector<Blob *> * blobVector)
{
	frameBlobs = blobVector;
}

vector<Blob*>* Data::getFrameBlobVector()
{
	return frameBlobs;
}

void Data::clearFrameBlobVector()
{
	frameBlobs->clear();
}
//================================================



