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
	void saveSettings();
};

#endif // !TRACKING_CC_HPP
