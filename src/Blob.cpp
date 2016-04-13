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



Blob::Blob(Point2f centroid, Rect rectangle, Mat ROI, Mat histogram)
{
	empty = false;

	this->hist = histogram;
	this->ROI = ROI;
	this->rect = rectangle;
	this->cent = centroid;
}



Blob::Blob(const Blob & blob)
{
	this->empty = blob.empty;

	this->hist = blob.hist;
	this->ROI = blob.ROI;
	this->rect = blob.rect;
	this->cent = blob.cent;
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






void Blob::setArea(int area)
{
	this->area = area;
}

int Blob::getArea()
{
	return area;
}







void Blob::setHist(Mat hist)
{
	this->hist = hist;
	empty = false;
}

Mat Blob::getHist()
{
	return hist;
}








void Blob::setROI(Mat ROI)
{
	this->ROI = ROI;
	empty = false;
}

Mat Blob::getROI()
{
	return ROI;
}








void Blob::setRect(Rect rect)
{
	this->rect = rect;
	empty = false;
}

Rect Blob::getRect()
{
	return rect;
}









void Blob::setCentroid(Point2f centroid)
{
	this->cent = centroid;
	empty = false;
}

Point2f Blob::getCentroid()
{
	return cent;
}
