#ifndef ABSTRACTSEGMENT_HPP
#define ABSTRACTSEGMENT_HPP

#include "Data.hpp"
#include "Settings.hpp"

#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

class AbstractSegment
{
	public:
		AbstractSegment(Data * data) {
			ptrData = data;
			out = new Mat(); //This Mat() is used to output the resulting image.
		};
		//VECTOR SHOULD DELETE out Mat

		virtual void segment() = 0; //Preform function and then call Data::addImage(Mat*)
		virtual void saveSettings() = 0;

	protected:
		Mat *out;
		Data *ptrData;
};

#endif // !ABSTRACTSEGMENT_HPP