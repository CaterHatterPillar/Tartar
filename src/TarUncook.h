#ifndef TARTAR_TARTAPE_H
#define TARTAR_TARTAPE_H

// Reads a tar-archive.

namespace Tartar {
	struct File;

	class StrmRdr;
}

#include <TartarBase.h>

namespace Tartar {
	class TarUncook : TartarBase {
	public:
		TarUncook( const char* p_targetTar );
		~TarUncook();

		bool init( Tar& io_t );
	protected:
	private:
		bool unpackTar( Tar& io_t, File& p_f );

		const char* m_targetTar;

		StrmRdr* m_tar;
	};
}

#endif // TARTAR_TARTAPE_H