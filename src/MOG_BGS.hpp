#ifndef MOG_BGS_HPP
#define MOG_BGS_HPP

#include <opencv2\video\background_segm.hpp>

#include "AbstractSegment.hpp"

using namespace cv;

class MOG_BGS : public AbstractSegment
{
	public:
		MOG_BGS(Data * data);
		~MOG_BGS();

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

#endif // !MOG_BGS_HPP