#include "Blob.hpp"



//===================CONSTRUCTOR DESTRUCTOR==========================
/**************************************************************************
Constructs an emptyblob. An Emptyblob is used to see if a path starts to loose its tracker

B - Blob
E - Emptyblob

 1  2  3  4  5  6
[B][B][B][B][E][E]
			 |_______The path is soon released

***************************************************************************/
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
