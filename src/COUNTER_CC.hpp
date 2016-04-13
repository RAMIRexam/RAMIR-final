#ifndef COUNTER_CC_HPP
#define COUNTER_CC_HPP

#include "AbstractCounting.hpp"
#include "Tools.hpp"

class COUNTER_CC : public AbstractCounting
{
	public:
		COUNTER_CC(Data *data);
		~COUNTER_CC();

		// Inherited via AbstractCounting
		void count();
		void saveSettings();

		int LSCheck(Point2f p);								//Line side check. Returns the side side of the eeline (entry exit line) the point is on

	private:

		//These two points defines the eeline
		Point* upperPoint;
		Point* lowerPoint;

		bool pauseForLineCheckDEBUG;

		int minTrackToBeCounted;							//How many tracks an object has to be tracked before it accepted into the ACTracker

		//COUNTERS
		int rightMovCnt;
		int leftMovCnt;

		int eelineX;
		int upperLineY;
		int lowerLineY;

		

};

#endif


