#include <cstring> // strcmp
#include <cstdlib> // atoi

#include <Tar.h>
#include <UStar.h>
#include <StrmRdr.h>

#include <TarUncook.h>

namespace Tartar {
	TarUncook::TarUncook( const char* p_targetTar ) : 
		TartarBase(),  
		m_targetTar( p_targetTar ) {
		m_tar = nullptr;
	}
	TarUncook::~TarUncook() {
		if( m_tar!=nullptr ) {
			delete m_tar;
		}
	}

	bool TarUncook::init( Tar& io_t ) {
		bool successInit = TartarBase::init();
		if( successInit==true ) {
			Tartar::File f;

			m_tar = new StrmRdr( m_targetTar );
			successInit = m_tar->init( f );
			if( successInit==true ) {
				successInit = unpackTar( io_t, f );
			} else {
				// Details surrounding error may be found in StrmRdr.
				// Do error handling based off of that.
			}
		}

		return successInit;
	}

	bool TarUncook::unpackTar( Tar& io_t, File& p_f ) {
		bool validTar = true;
		
		UStar hdr;
		char* p = p_f.fileData;
		
		std::memcpy( &hdr, p, g_UStar_Size);
		bool isUStarHdr = (std::strcmp(hdr.ustarIctr, g_UStar_Indicator) == 0);
		while( isUStarHdr==true ) { // Is UStar-header.
			p += g_UStar_Size; // Jump header.

			// Get file contents:
			unsigned long fileSize = std::atoi( hdr.fileSize ); // Currently stored as decimal.

			char* file = new char[fileSize];
			std::memcpy( file, p, fileSize );
			// ...and add it to resulting data type:
			io_t.push( fileSize, file );

			// Calc and control checksum here. Remember that the checksum is currently stored octal.
			//validTar = ...

			// Jump already read file and the remaining bytes up to 512:
			p += fileSize;
			while( (fileSize%sizeof(UStar)) != 0 ) {
				p++;
				fileSize++;
			}

			// Read new header and check whether or not valid UStar-header:
			std::memcpy( &hdr, p, g_UStar_Size);
			isUStarHdr = !((bool)std::strcmp(hdr.ustarIctr, g_UStar_Indicator));
		}

		return validTar;
	}
}