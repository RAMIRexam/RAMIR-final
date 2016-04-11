#include "Blob.hpp"



//===================CONSTRUCTOR DESTRUCTOR==========================

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
