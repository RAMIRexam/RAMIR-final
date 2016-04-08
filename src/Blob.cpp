#include "Blob.hpp"



//===================CONSTRUCTOR DESTRUCTOR==========================

Blob::Blob()
{
	empty = true;
}

Blob::Blob(Mat histogram, Rect rectangle, Mat ROI, Point2f centroid)
{
	empty = false;

	this->hist = histogram;
	this->ROI = ROI;
	this->rect = rectangle;
	this->cent = centroid;
}

Blob::~Blob()
{
	hist.release();
	ROI.release();
}


//================================================================




bool Blob::isEmpty()
{
	return empty;
}

Mat Blob::getHist()
{
	return hist;
}

Mat Blob::getROI()
{
	return ROI;
}

Rect Blob::getRect()
{
	return rect;
}

Point2f Blob::getCentroid()
{
	return cent;
}
