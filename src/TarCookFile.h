#ifndef TARTAR_TARCOOKFILE_H
#define TARTAR_TARCOOKFILE_H

// Creates a tar-archive.

namespace Tartar {
	struct UStar;

	class StrmWtr;
}

#include <TartarBase.h>

namespace Tartar {
	class TarCookFile : public TartarBase {
	public:
		TarCookFile( const char* p_tarName );
		~TarCookFile();

		bool init();
		void done();

		bool cookFile( const char* p_filename );
	protected:
	private:
		bool initHdr( UStar& io_hdr, const char* p_fileName, unsigned long p_fileSize );
		void cook( UStar& p_hdr, const char* p_data, unsigned long p_dataSize );

		const char* m_tarName;
		StrmWtr* m_strmTar;
	};
}

#endif //TARTAR_TARCOOKFILE_H