#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <time.h>
#include <vector>

#include "Tools.hpp"
#include "Input.hpp"
#include "Display.hpp"
#include "Statistic.hpp"
#include "Definitions.hpp"

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

//Tracking
#include "TRACKING.hpp"
#include "TRACKING_GHOST.hpp"
#include "TRACKING_CC.hpp"

//Counting
#include "COUNTER_ONE.hpp"
#include "COUNTER_ONE_HYST.hpp"
#include "COUNTER_TWO.hpp"
#include "COUNTER_CC.hpp"

#include "AbstractSegment.hpp"
#include "AbstractFilter.hpp"
#include "AbstractDetection.hpp"
#include "AbstractTracking.hpp"
#include "AbstractCounting.hpp"

//---------------------------
#include <fstream>
#include <sstream>
#include <string>
//---------------------------

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
		string dateTime;
		int nImagesSaved;
		Mat lastImage;
		int frameNr;
		Mat *graph1;
		Mat *graph2;

		Input *input;
		Display *display;
		Data *data;
		
		vector<AbstractSegment *>		*segmentObjectVector;
		vector<AbstractFilter *>		*filterObjectVector;
		vector<AbstractDetection *>		*detectionObjectVector;
		vector<AbstractTracking *>		*trackingObjectVector;
		vector<AbstractCounting *>		*countingObjectVector;

		bool buttonControl();
		void record();
		void pause();

		void initGraph();
		void drawGraphUp(Point point);
		void drawGraphDown(Point point);

		void saveSettings();

};
#endif // !APPLICATION_HPP
