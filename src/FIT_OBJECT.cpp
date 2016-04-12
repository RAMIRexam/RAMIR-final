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
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;

	vector<Blob *> *blobVector = new vector<Blob *>();

	//====================================================
	int hbins = 30, sbins = 32;
	int histSize[] = { hbins, sbins };
	float hranges[] = { 0, 180 };
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	int channels[] = { 0 };
	//=====================================================

	Mat temp, hist;
	ptrData->getLastImage()->copyTo(temp);

	findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	ptrData->getLastImage()->copyTo(*out);
	cvtColor(*out, *out, CV_GRAY2BGR, 3);

	//Calculate blob data
	for (vector<Point> cont : contours)
	{

		//calculates a bounding rectangle around the contour
		Rect rect = boundingRect(cont);


		//Creates a ROI on same spot as the rectangle
		Mat blobROI(ptrData->getLastImage()->clone(), rect);

		
		Mat test(rect.height, rect.width, blobROI.type(), Scalar(0));
		ellipse(test, Point(test.cols / 2, test.rows / 2), Size(test.cols / 2, test.rows / 2), 0, 0, 360, Scalar(255), -1);
		Mat h1;
		
		if (test.cols > 40 && test.rows > 40)
		{
			//Calculates the histogram for the ROI, NOT USED EVER!!!!
			calcHist(&blobROI, 1, channels, Mat(), hist, 2, histSize, ranges);
			normalize(hist, hist, 0, 1, NORM_MINMAX, -1, Mat());

			calcHist(&test, 1, channels, Mat(), h1, 2, histSize, ranges);
			normalize(h1, h1, 0, 1, NORM_MINMAX, -1, Mat());

			compareHist(hist, h1, CV_COMP_CORREL);
		}

		//Find the centroid at the contour
		Moments m = moments(cont, false);
		Point2f cent = Point2f(m.m10 / m.m00, m.m01 / m.m00);

		if (m.m00 > areaLimit_3P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(0, 0, 255), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(255, 0, 0), 2);	//TEST CODE!
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m.m00 > areaLimit_2P)
		{
			ellipse(*out, cent, Size(10, 10), 0.0, 0.0, 360.0, Scalar(255, 0, 0), 2); //TEST CODE!
			rectangle(*out, rect, Scalar(0, 255, 0), 2);	//TEST CODE!
			blobVector->push_back(new Blob(cent, rect, blobROI));
			blobVector->push_back(new Blob(cent, rect, blobROI));
		}
		else if (m.m00 > areaLimit_1P)
		{
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
