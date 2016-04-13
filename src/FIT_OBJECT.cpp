#include "FIT_OBJECT.hpp"



FIT_OBJECT::FIT_OBJECT(Data * data) : AbstractDetection(data)
{
	areaLimit_1P = 4000;
	areaLimit_2P = 8000;
	areaLimit_3P = 12000;
}


FIT_OBJECT::~FIT_OBJECT()
{
}






void FIT_OBJECT::detect()
{
	vector<Vec4i> hierarchy1;
	vector<vector<Point> > contours;

	vector<Blob *> *blobVector = new vector<Blob *>();


	Mat temp;
	ptrData->getLastImage()->copyTo(temp);

	findContours(temp, contours, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	ptrData->getLastImage()->copyTo(*out);
	cvtColor(*out, *out, CV_GRAY2BGR, 3);

	//Calculate blob data
	for (vector<Point> cont : contours)
	{

		//calculates a bounding rectangle around the contour
		Rect rect = boundingRect(cont);


		//Creates a ROI on same spot as the rectangle
		Mat blobROI(ptrData->getLastImage()->clone(), rect);		


		//Find the centroid at the contour
		Moments m1 = moments(cont, false);
		Point2f cent = Point2f(m1.m10 / m1.m00, m1.m01 / m1.m00);


		if (m1.m00 > areaLimit_3P)
		{
			if (m1.m00 <= (blobROI.cols / 2) * (blobROI.rows / 2) * 3.1415)
			{
				ellipse(*out, cent, Size(blobROI.cols, blobROI.rows), 0.0, 0.0, 360.0, Scalar(255, 255, 255), -1); //TEST CODE!
			}

			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 0, 255), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(255, 0, 0), 2);	//TEST CODE!

			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m1.m00 > areaLimit_2P)
		{
			if (m1.m00 <= (blobROI.cols / 2) * (blobROI.rows / 2) * 3.1415)
			{
				ellipse(*out, cent, Size(blobROI.cols, blobROI.rows), 0.0, 0.0, 360.0, Scalar(255, 255, 255), -1); //TEST CODE!
			}

			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(255, 0, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 255, 0), 2);	//TEST CODE!

			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m1.m00 > areaLimit_1P)
		{
			if (m1.m00 <= (blobROI.cols / 2) * (blobROI.rows / 2) * 3.1415)
			{
				ellipse(*out, cent, Size(blobROI.cols / 2, blobROI.rows / 2), 0.0, 0.0, 360.0, Scalar(255, 255, 255), -1); //TEST CODE!
			}

			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 255, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 0, 255), 2);	//TEST CODE!

			blobVector->push_back(new Blob(cent, rect, blobROI));
		}

	}

	ptrData->setFrameBlobVector(blobVector);
	ptrData->addImage(out); //UNNECESSARY? TEST CODE!
}

void FIT_OBJECT::saveSettings()
{
}
