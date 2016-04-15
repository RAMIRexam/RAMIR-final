#ifndef BLOB_HPP
#define BLOB_HPP

#include <opencv2\core.hpp>

using namespace cv;

class Blob
{
	public:
		Blob();
		Blob(Point2f centroid, bool ghostBlob, Rect rectangle = Rect(), Mat ROI = Mat(), Mat histogram = Mat());
		Blob(Point2f centroid, Rect rectangle = Rect(), Mat ROI = Mat(), Mat histogram = Mat());
		Blob(const Blob &blob);		//copy constructor
		~Blob();

		bool isEmpty();
		bool isGhost();
		
		void setArea(int area);
		int getArea();

		void setHist(Mat hist);
		Mat getHist();

		void setROI(Mat ROI);
		Mat getROI();

		void setRect(Rect rect);
		Rect getRect();

		void setCentroid(Point2f centroid);
		Point2f getCentroid();

	private:
		bool empty;
		bool ghostBlob;

		int area;
		Mat hist;
		Mat ROI;
		Rect rect;
		Point2f cent;
};

#endif // !BLOB_HPP