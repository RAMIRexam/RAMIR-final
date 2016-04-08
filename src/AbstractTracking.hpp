#ifndef ABSTRACTTRACKING_HPP
#define ABSTRACTTRACKING_HPP

#include "Data.hpp"
#include "Settings.hpp"

#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

class AbstractTracking
{
	public:
		AbstractTracking(Data * data) {
			ptrData = data;
			out = new Mat(); //This Mat() is used to output the resulting image.
		};
		//VECTOR SHOULD DELETE Out Mat

		virtual void track() = 0; //Preform function and then call Data::addImage(Mat*)
		virtual void saveSettings() = 0;

	protected:
		Mat *out;
		Data *ptrData;
};

#endif // !ABSTRACTTRACKING_HPP
