#ifndef DETECTION_HPP
#define DETECTION_HPP

#include "AbstractDetection.hpp"

#include <opencv2\opencv.hpp>

class DETECTION : public AbstractDetection
{
	public:
		DETECTION(Data *data);
		~DETECTION();

		// Inherited via AbstractDetection
		void detect();
		void saveSettings();

	private:
		int areaLimit_1P;
		int areaLimit_2P;
		int areaLimit_3P;

		static void setAreaLimit_1P(int value, void *userData);
		static void setAreaLimit_2P(int value, void *userData);
		static void setAreaLimit_3P(int value, void *userData);

};

#endif // !DETECTION_HPP

