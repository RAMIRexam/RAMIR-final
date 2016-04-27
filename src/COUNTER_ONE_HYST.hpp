#ifndef COUNTER_ONE_HYST_HPP
#define COUNTER_ONE_HYST_HPP

#include "AbstractCounting.hpp"
#include "Tools.hpp"

#include <iostream>

using namespace std;

class COUNTER_ONE_HYST : public AbstractCounting
{
	public:
		COUNTER_ONE_HYST(Data *data);
		~COUNTER_ONE_HYST();

		// Inherited via AbstractCounting
		void count();
		void saveSettings();

	private:
		int lineHyst;

		int textColorLeftB;
		int textColorLeftG;
		int textColorLeftR;

		int textColorRightB;
		int textColorRightG;
		int textColorRightR;

		static void setHyst(int value, void * userdata);

};

#endif // !COUNTER_ONE_HYST_HPP