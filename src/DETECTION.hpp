#ifndef DETECTION_HPP
#define DETECTION_HPP

#include "AbstractDetection.hpp"

#include <opencv2\opencv.hpp>


/**
	Detects blobs using moments function from opencv
*/
class DETECTION : public AbstractDetection
{
	public:
		DETECTION(Data *data);
		~DETECTION();

		// Inherited via AbstractDetection
		void detect();
		void saveSettings();

	private:
};

#endif // !DETECTION_HPP

