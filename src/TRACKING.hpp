#ifndef TRACKING_HPP
#define TRACKING_HPP

#include "AbstractTracking.hpp"

#include <opencv2\opencv.hpp>

class TRACKING : public AbstractTracking
{
	public:
		TRACKING(Data *data);
		~TRACKING();

		// Inherited via AbstractTracking
		void track();
		void saveSettings();
};

#endif // !TRACKING_HPP
