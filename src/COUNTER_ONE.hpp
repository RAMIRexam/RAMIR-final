#ifndef COUNTER_ONE_HPP
#define COUNTER_ONE_HPP

#include "AbstractCounting.hpp"
#include "Tools.hpp"

class COUNTER_ONE: public AbstractCounting
{
	public:
		COUNTER_ONE(Data *data);
		~COUNTER_ONE();

		// Inherited via AbstractCounting
		void count();
		void saveSettings();

	private:
		int left2Right;
		int right2Left;

		int textColorLeftB;
		int textColorLeftG;
		int textColorLeftR;

		int textColorRightB;
		int textColorRightG;
		int textColorRightR;

};

#endif // !COUNTER_ONE_HPP