#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>

#include "Input.hpp"
#include "Display.hpp"

//Segment
#include "BGS.hpp"
#include "MOG_BGS.hpp"
#include "MOG_BGS_HSV.hpp"
#include "ROI_BG.hpp"

//Filter
#include "ERODE.hpp"
#include "DILATE.hpp"

//Detection
#include "DETECTION.hpp"
#include "FIT_OBJECT.hpp"

//Tracking
#include "TRACKING.hpp"

//Counting
#include "COUNTER_ONE.hpp"
#include "COUNTER_TWO.hpp"

#include "AbstractSegment.hpp"
#include "AbstractFilter.hpp"
#include "AbstractDetection.hpp"
#include "AbstractTracking.hpp"
#include "AbstractCounting.hpp"

using namespace std;

class Application
{
	public:
		Application();
		Application(int);
		Application(char *);
		~Application();

		void start();

		void addSegment(AbstractSegment *segmentObject);
		void addFilter(AbstractFilter *filterObject);
		void addDetection(AbstractDetection *detectionObject);
		void addTracking(AbstractTracking *trackingObject);
		void addCounting(AbstractCounting *countingObject);
		
	private:
		Input *input;
		Display *display;
		
		vector<AbstractSegment *>		*segmentObjectVector;
		vector<AbstractFilter *>		*filterObjectVector;
		vector<AbstractDetection *>		*detectionObjectVector;
		vector<AbstractTracking *>		*trackingObjectVector;
		vector<AbstractCounting *>		*countingObjectVector;
		
};
#endif // !APPLICATION_HPP
