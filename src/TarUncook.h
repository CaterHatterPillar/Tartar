#ifndef TARTAR_TARUNCOOK_H
#define TARTAR_TARUNCOOK_H

// Reads a tar-archive.
// Note to self: Implement flags to specify checksum-validation etc.

namespace Tartar {
	struct File;
	
	class Tar;
	class StrmRdr;
}

#include <TarCook.h>

namespace Tartar {
	class TarUncook : TarCook {
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

#endif // TARTAR_TARUNCOOK_H