#ifndef COUNTER_ONE_HPP
#define COUNTER_ONE_HPP

#include "AbstractCounting.hpp"
#include "Tools.hpp"

#include <iostream>

using namespace std;

class COUNTER_ONE: public AbstractCounting
{
	public:
		COUNTER_ONE(Data *data);
		~COUNTER_ONE();

		// Inherited via AbstractCounting
		void count();
		void saveSettings();

	private:

		int textColorLeftB;
		int textColorLeftG;
		int textColorLeftR;

		int textColorRightB;
		int textColorRightG;
		int textColorRightR;

};

#endif // !COUNTER_ONE_HPP