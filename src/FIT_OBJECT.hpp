#ifndef FIT_OBJECT_HPP
#define FIT_OBJECT_HPP

#include "AbstractDetection.hpp"

class FIT_OBJECT : public AbstractDetection
{
	public:
		FIT_OBJECT(Data *data);
		~FIT_OBJECT();

		// Inherited via AbstractDetection
		void detect();
		void saveSettings();

	private:
		int areaLimit_1P;
		int areaLimit_2P;
		int areaLimit_3P;
};

#endif // !FIT_OBJECT_HPP





