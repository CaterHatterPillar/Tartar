#include <fstream>

#include <UStar.h>
#include <Tartar.h>

namespace Tartar {
	Tartar::Tartar( const char* p_tarName ) : m_tarName( p_tarName ) {
		m_prevError = PrevErrors_NA;

		m_strmInput	= nullptr;
		m_strmTar	= nullptr;
	}
	Tartar::~Tartar() {
		if( m_strmInput!=nullptr ) {
			if( m_strmInput->is_open() ) {
				m_strmInput->close();
			}
			delete m_strmInput;
		}
		if( m_strmTar!=nullptr ) {
			if( m_strmTar->is_open() ) {
				m_strmTar->close();
			}
			delete m_strmTar;
		}
	}

	bool Tartar::init() {
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

		// Initialize other vars.
		m_strmInput = new std::ifstream();

		return successInit;
	}

	bool Tartar::strmTarIsGood() {
		if( !m_strmTar->is_open() )	{
			m_prevError = PrevErrors_TAR_NOT_FOUND;
		} 
		Tartar::IOErrors strmError = getStrmStatus( m_strmTar );
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
	Tartar::IOErrors Tartar::getStrmStatus( std::ios* p_strm ) {
		Tartar::IOErrors ioErrors = IOErrors_NA;
		if( p_strm->eof() ) {
			ioErrors = IOErrors_EOF;
		} else if( p_strm->bad() ) {
			ioErrors = IOErrors_BAD;
		} else if( p_strm->fail() ) {
			ioErrors = IOErrors_FAIL;
		}
		return ioErrors;
	}

	bool Tartar::tarchiveFile( const char* p_filename ) {
		bool successTarchive = false;

		m_strmInput->open( p_filename );
		successTarchive = getStrmStatus(m_strmInput);
		if( successTarchive==IOErrors_NA ) { // File has successfully been found and opened.
			const char* archiveFileName = p_filename; // Consider making this into an argument.
			
			// Create UStar header for the file in question:
			UStar hdr;
			initHdr( hdr, archiveFileName );

			//Don't forget to close the file.
			m_strmInput->close();
		} 

		return successTarchive;
	}

	bool Tartar::initHdr( UStar& io_hdr, const char* p_fileName ) {
		// The header-initialization function currrently disregards certain elements 
		// in the header such as file last modified, file mode, user name and user group name.
		bool hdrGood = true;

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
		//_size((void*)&header,len);

		// Set checkum of header:
		//_checksum((void*)&header);
	}
}