#include <fstream>

#include <UStar.h>
#include <StrmRdr.h>
#include <Tarchive.h>

namespace Tartar {
	Tarchive::Tarchive( const char* p_tarName ) : m_tarName( p_tarName ) {
		m_prevError = PrevErrors_NA;

		m_strmTar	= nullptr;
	}
	Tarchive::~Tarchive() {
		if( m_strmTar!=nullptr ) {
			if( m_strmTar->is_open() ) {
				m_strmTar->close();
			}
			delete m_strmTar;
		}
	}

	bool Tarchive::init() {
		bool successInit = true;

		// Control header size.
		if( sizeof(UStar)!=g_UStar_Size ) {
			m_prevError = PrevErrors_UNEXPECTED_HEADER_SIZE;
			successInit = false;
		}

		// Create the resulting tar-file.
		m_strmTar = new std::ofstream();
		m_strmTar->open( m_tarName, std::ios::out );
		successInit = strmTarIsGood();

		return successInit;
	}

	void Tarchive::done() {
		// The end of an archive is marked by at least two consecutive zero-filled records. 
		// The final block of an archive is padded out to full length with zero bytes.

		// Write closing statement to tar:
		UStar emptyHdr; // Default constructor nulls it for us.
		m_strmTar->write( (char*)(&emptyHdr), sizeof(UStar) );
		m_strmTar->write( (char*)(&emptyHdr), sizeof(UStar) );

		// Then close and complete our tar-archive:
		if( m_strmTar!=nullptr ) {
			if( m_strmTar->is_open() ) {
				m_strmTar->close();
			}
		}
	}

	bool Tarchive::strmTarIsGood() {
		if( !m_strmTar->is_open() )	{
			m_prevError = PrevErrors_TAR_NOT_FOUND;
		} 
		Tarchive::IOErrors strmError = getStrmStatus( m_strmTar );
		switch( strmError ) {
		case IOErrors_EOF:
			m_prevError = PrevErrors_TAR_EOF;
			break;
		case IOErrors_BAD:
			m_prevError = PrevErrors_TAR_BAD;
			break;
		case IOErrors_FAIL:
			m_prevError = PrevErrors_TAR_FAIL;
			break;
		}

		bool strmTarIsGood = true;
		if( m_prevError!=PrevErrors_NA ) {
			strmTarIsGood = false;
		}

		return strmTarIsGood;
	}
	Tarchive::IOErrors Tarchive::getStrmStatus( std::ios* p_strm ) {
		Tarchive::IOErrors ioErrors = IOErrors_NA;
		if( p_strm->eof() ) {
			ioErrors = IOErrors_EOF;
		} else if( p_strm->bad() ) {
			ioErrors = IOErrors_BAD;
		} else if( p_strm->fail() ) {
			ioErrors = IOErrors_FAIL;
		}
		return ioErrors;
	}

	bool Tarchive::tarchiveFile( const char* p_filename ) {
		bool successTarchive = false;

		File f;

		StrmRdr strmRdr(p_filename);
		bool strmOK = strmRdr.init( f );
		if( strmOK ) {
			const char* archiveFileName = p_filename; // Consider making this into an argument.

			// Create UStar header for the file in question:
			UStar hdr;
			successTarchive = initHdr( hdr, archiveFileName, f.fileSize );

			// Archive the data:
			tarchive( hdr, f.fileData, f.fileSize );

			successTarchive = true;
		}

		return successTarchive;
	}

	bool Tarchive::initHdr( UStar& io_hdr, const char* p_fileName, unsigned long p_fileSize ) {
		// The header-initialization function currrently disregards certain elements 
		// in the header such as file last modified, file mode, user name and user group name.
		bool hdrGood = true;

		// Set tar header specification:
		std::sprintf( io_hdr.ustarIctr, g_UStar_Indicator );

		// Set filename:
		unsigned int nameChars = std::strlen( p_fileName );
		if( p_fileName!=nullptr && nameChars<UStar::sFilename ) {
			std::sprintf( io_hdr.filename, p_fileName );
		} else {
			hdrGood |= false;
		}

		// Set link indicator field:
		io_hdr.linkIctr[0] = g_UStar_LinkIndicator_Normal;

		// Set length of file:
		std::sprintf( io_hdr.fileSize, "%011llo",  (long long unsigned int)p_fileSize );

		// Set checkum of header:
		unsigned int checksum = calcChecksumHdr( &io_hdr );
		std::sprintf( io_hdr.checksum, "%06o", checksum );

		return hdrGood;
	}

	unsigned int Tarchive::calcChecksumHdr( UStar* p_hdr ) {
		unsigned int checksum = 0;
		/*The checksum is calculated by taking the sum of the unsigned byte values 
		| of the header record with the eight checksum bytes taken to be ascii 
		| spaces (decimal value 32). It is stored as a six digit octal number 
		| with leading zeroes followed by a NUL and then a space.*/

		char* curByte = (char*)p_hdr;
		while( curByte < p_hdr->checksum ) {
			// Sum the values up to the checksum:
			checksum += *curByte++ & 0xff;
		}
		for( unsigned int i = 0; i < 8; ++i ) {
			// Treat the checksum-byets as ascii-spaces:
			checksum += ' ';
			curByte++;
		}
		char* endByte = (char*)p_hdr + sizeof(UStar);
		while( curByte < endByte ) {
			// Sum the remaining values into the checksum:
			checksum += *curByte++ & 0xff;
		}

		return checksum;
	}

	void Tarchive::tarchive( UStar& p_hdr, const char* p_data, unsigned long p_dataSize ) {
		// Write header to tar:
		m_strmTar->write( (char*)(&p_hdr), sizeof(UStar) );

		// Write file to tar:
		m_strmTar->write( p_data, p_dataSize );

		// The final block of an archive is padded out to full length with zero bytes. [Wikipedia]
		char nullChar = '\0';
		unsigned long curChar = p_dataSize;
		while( (curChar%sizeof(UStar)) != 0 ) {
			m_strmTar->write( &nullChar, sizeof(char) );
			curChar++;
		}
	}
}