#ifndef TRACKING_CC_HPP
#define TRACKING_CC_HPP

#include "AbstractTracking.hpp"

#include <opencv2\opencv.hpp>

class TRACKING_CC : public AbstractTracking
{
public:
	TRACKING_CC(Data *data);
	~TRACKING_CC();

	// Inherited via AbstractTracking
	void track();
	vector<Path*> AutomaticTracking(vector<Path*> trackers, vector<Path*> ACTrackers);		//function with the code from "part 1" in the examwork
	void saveSettings();

	vector<Path*> intersectionTest(vector<Blob*>* blobs, vector<Path*> trackers);

private:

	int trackerLife;
};

#endif // !TRACKING_CC_HPP


