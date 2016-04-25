#ifndef COUNTER_TWO_HPP
#define COUNTER_TWO_HPP

#include "AbstractCounting.hpp"
#include "Tools.hpp"

#include <iostream>

class COUNTER_TWO : public AbstractCounting
{
	public:
		COUNTER_TWO(Data *data);
		~COUNTER_TWO();

		// Inherited via AbstractCounting
		void count();
		void saveSettings();

	private:

};

#endif // !COUNTER_TWO_HPP



