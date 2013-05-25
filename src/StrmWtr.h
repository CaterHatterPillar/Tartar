#ifndef TARTAR_STRMWTR_H
#define TARTAR_STRMWTR_H

#include <Strm.h>

namespace Tartar {
	class StrmWtr : public Strm {
	public:
		StrmWtr( const char* p_filepath );
		~StrmWtr();

		bool init();
		void done();

		void push( const char* p_fileData, unsigned long p_fileSize );
	protected:
	private:
		std::ofstream* m_strmO;
	};
}

#endif //TARTAR_STRMWTR_H