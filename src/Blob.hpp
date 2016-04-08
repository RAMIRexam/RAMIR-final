#ifndef BLOB_HPP
#define BLOB_HPP

#include <opencv2\core.hpp>

using namespace cv;

class Blob
{
	public:
		Blob();
		Blob(Mat histogram, Rect rectangle, Mat ROI, Point2f centroid);
		~Blob();

		bool isEmpty();
		Mat getHist();
		Mat getROI();
		Rect getRect();
		Point2f getCentroid();

	private:
		bool empty;
		Mat hist;
		Mat ROI;
		Rect rect;
		Point2f cent;
};

#endif // !BLOB_HPP