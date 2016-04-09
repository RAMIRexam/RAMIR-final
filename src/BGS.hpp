#ifndef BGS_HPP
#define BGS_HPP

#include "AbstractSegment.hpp"

class BGS : public AbstractSegment
{
	public:
		BGS(Data *data);
		~BGS();

		// Inherited via AbstractSegment
		void segment();
		void saveSettings();

	private:
};

#endif // !BGS_HPP



