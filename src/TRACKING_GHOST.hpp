#ifndef TRACKING_GHOST_HPP
#define TRACKING_GHOST_HPP

#include "AbstractTracking.hpp"

#include <opencv2\opencv.hpp>

class TRACKING_GHOST : public AbstractTracking
{
public:
	TRACKING_GHOST(Data *data);
	~TRACKING_GHOST();

	// Inherited via AbstractTracking
	void track();
	void saveSettings();
};

#endif // !TRACKING_GHOST_HPP
