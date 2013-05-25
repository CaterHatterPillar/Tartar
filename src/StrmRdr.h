#ifndef TARTAR_STRMRDR_H
#define TARTAR_STRMRDR_H

namespace Tartar {
	struct File;
}

#include <Strm.h>

namespace Tartar {
	class StrmRdr : public Strm {
	public:
		StrmRdr( const char* p_filepath );
		~StrmRdr();

		bool init( File& io_f );
	protected:
	private:
		std::ifstream* m_strmI;
	};
}

#endif //TARTAR_STRMRDR_H