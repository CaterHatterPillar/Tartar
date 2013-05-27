#include <Tar.h>
#include <UStar.h>
#include <StrmRdr.h>
#include <StrmWtr.h>

#include <TarCookFile.h>

// For reference when it comes to printf-formats:
// http://www.cplusplus.com/reference/cstdio/printf/

namespace Tartar {
	TarCookFile::TarCookFile( const char* p_tarName ) : 
		TarCook(), 
		m_tarName( p_tarName ) {
		m_strmTar = nullptr;
	}
	TarCookFile::~TarCookFile() {
		if( m_strmTar!=nullptr ) {
			delete m_strmTar;
		}
	}

	bool TarCookFile::init() {
		// Call TartarBase-init to secure default stuff:
		bool successInit = TarCook::init();
		if( successInit==true ) {
			// Prepare the resulting tar-file.
			m_strmTar = new StrmWtr( m_tarName );
			successInit = m_strmTar->init();
			if( successInit!=true ) {
				// Error flags may be retrieved from StrmRdr.
				// Do some error handling based off those.
				m_lastError = TartarErrors_UNKNOWN_OUTPUT;
			}
		}

		return successInit;
	}

	void TarCookFile::done() {
		// The end of an archive is marked by at least two consecutive zero-filled records. 
		// The final block of an archive is padded out to full length with zero bytes.

		// Write closing statement to tar:
		UStar emptyHdr; // Default constructor nulls it for us.
		m_strmTar->push( (char*)(&emptyHdr), sizeof(UStar) );
		m_strmTar->push( (char*)(&emptyHdr), sizeof(UStar) );

		// Then close and complete our tar-archive:
		m_strmTar->done();
	}

	bool TarCookFile::cookFile( const char* p_filename ) {
		bool successTarchive = false;

		Tartar::File f;

		StrmRdr strmFile(p_filename);
		bool strmOK = strmFile.init( f );
		if( strmOK ) {
			const char* archiveFileName = p_filename; // Consider making this into an argument.

			// Create UStar header for the file in question:
			UStar hdr;
			successTarchive = cookHdr( hdr, archiveFileName, f.fileSize );

			// Archive the data:
			cook( hdr, f.fileData, f.fileSize );

			successTarchive = true;
		} else {
			// Error flags may be retrieved from StrmRdr.
			// Do some error handling based off those.
			m_lastError = TartarErrors_UNKNOWN_INPUT;
		}

		return successTarchive;
	}

	void TarCookFile::cook( UStar& p_hdr, const char* p_data, unsigned long p_dataSize ) {
		// Write header to tar:
		m_strmTar->push( (char*)(&p_hdr), sizeof(UStar) );

		// Write file to tar:
		m_strmTar->push( p_data, p_dataSize );

		// The final block of an archive is padded out to full length with zero bytes. [Wikipedia]
		char nullChar = '\0';
		unsigned int padNum = getPadNum( p_dataSize, sizeof(UStar) );
		for( unsigned int i = 0; i < padNum; i++ ) {
			m_strmTar->push( &nullChar, sizeof(char) );
		}
		
		//unsigned long curChar = p_dataSize;
		//while( (curChar%sizeof(UStar)) != 0 ) {
		//	m_strmTar->push( &nullChar, sizeof(char) );
		//	curChar++;
		//}
	}
}