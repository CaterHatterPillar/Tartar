#ifndef TARTAR_TARCOOK_H
#define TARTAR_TARCOOK_H

// Creates a tar-archive.

namespace Tartar {
	struct UStar;

	class StrmWtr;
}

#include <TartarBase.h>

namespace Tartar {
	class TarCook : public TartarBase {
	public:
		TarCook( const char* p_tarName );
		~TarCook();

		bool init();
		void done();

		bool tarchiveFile( const char* p_filename );
	protected:
	private:
		bool initHdr( UStar& io_hdr, const char* p_fileName, unsigned long p_fileSize );
		unsigned int calcChecksumHdr( UStar* p_hdr );
		void tarchive( UStar& p_hdr, const char* p_data, unsigned long p_dataSize );

		const char* m_tarName;
		StrmWtr* m_strmTar;
	};
}

#endif //TARTAR_TARCOOK_H