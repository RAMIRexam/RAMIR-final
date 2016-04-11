#ifndef AREA_DETECT_HPP
#define AREA_DETECT_HPP

#include "AbstractDetection.hpp"

/**
	Requires that the blobs have been extracted
*/
class AREA_DETECT : public AbstractDetection
{
	public:
		AREA_DETECT(Data *data);
		~AREA_DETECT();

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

#endif // !AREA_DETECT_HPP



