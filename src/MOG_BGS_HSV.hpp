#ifndef MOG_BGS_HSV_HPP
#define MOG_BGS_HSV_HPP

#include <opencv2\video\background_segm.hpp>

#include "AbstractSegment.hpp"

using namespace cv;

class MOG_BGS_HSV : public AbstractSegment
{
	public:
		MOG_BGS_HSV(Data * data);
		~MOG_BGS_HSV();

		// Inherited via AbstractSegment
		void segment();
		void saveSettings();

	private:
		Ptr<BackgroundSubtractor> pMOG;

		int history;
		int threshold;
		bool shadows;

		static void setHistory(int value, void *userdata);
		static void setThreshold(int value, void *userdata);
};

#endif // !MOG_BGS_HSV_HPP




