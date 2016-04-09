/*
TRACKER_CC = "tracker counted check"
*/

#include "TRACKING_CC.hpp"


TRACKING_CC::TRACKING_CC(Data * data) : AbstractTracking(data)
{

}


TRACKING_CC::~TRACKING_CC()
{
}




void TRACKING_CC::track()
{
	vector<Path *> *paths = ptrData->getPathVector();
	vector<Blob *> *blobs = ptrData->getFrameBlobVector();

	ptrData->getLastImage()->copyTo(*out);

	
	/*
	/	Tests:
	/		(1) Check if all trackers is processed at the end
	/
	*/

	for (Path *p : *paths) {
		p->
	}


	if (ACTrackers.size() > 0) {									//if there exists already counted trackers, the blobs belonging to this trackers must first be removed
		ACTrackers = intersectionTest(&blobs, ACTrackers);			//intersectionTest will move blobs to "already counted trackers"
	}


	if (trackers.size() == 0) {
		for (Blob b : blobs) {										//No trackers exists. All blobs will turn to a tracker
			int lineSide = scene->LSCheck(b);
			Tracker *t = new Tracker(lineSide, b, trackerLife);

			t->processed = true;
			trackers.push_back(t);

		}
	}

	else {
		trackers = intersectionTest(&blobs, trackers);				//there already exists trackers, intersectionTest will move blobs to trackers

		for (Blob b : blobs) {										//iterate throught the rest of the blobs and create trackers for them
			int lineSide = scene->LSCheck(b);
			Tracker *t = new Tracker(lineSide, b, trackerLife);

			t->processed = true;
			trackers.push_back(t);

		}

		for (Tracker *t : trackers) {
			if (!t->processed) {									//if tracker is not processed, fill it with emptyblob
				t->fillWithEmptyBlob();
				t->processed = true;
			}
		}
	}


	for (Tracker *t : trackers) {
		assert(t->processed == true);								//(1) DEBUG
	}

	trackers = trackerSurvivalTest(trackers);						//decrement trackerlife. If trackerlife is 0 the tracker is removed
	ACTrackers = trackerSurvivalTest(ACTrackers);					//decrement trackerlife. If trackerlife is 0 the tracker is removed


	for (Tracker *t : trackers) { t->processed = false; }				//reset processed for next iteration
	for (Tracker *t : ACTrackers) { t->processed = false; }			//reset processed for next iteration


	return trackers;
}

void TRACKING_CC::saveSettings()
{
}
