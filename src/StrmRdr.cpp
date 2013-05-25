#include <fstream>

#include <Strm.h>
#include <StrmRdr.h>

namespace Tartar {
	StrmRdr::StrmRdr( const char* p_filepath ) : m_filepath( p_filepath ) {
		m_strmStatus = IOErrors_NA;

		m_strmI = nullptr;
	}
	StrmRdr::~StrmRdr() {
		if( m_strmI!=nullptr ) {
			if( m_strmI->is_open()==true ) {
				m_strmI->close();
			}
			delete m_strmI;
		}
	}

	bool StrmRdr::init( File& io_f ) {
		bool successInit = false;

		m_strmI = new std::ifstream();
		m_strmI->open( m_filepath, std::ios_base::binary );
		if( m_strmI->is_open()==true ) {
			successInit = true;

			// Get length of file:
			m_strmI->seekg( 0, std::ios::end );
			io_f.fileSize = m_strmI->tellg();
			m_strmI->seekg( 0, std::ios::beg );

			// Get contents of file:
			io_f.fileData = new char[ io_f.fileSize ];
			m_strmI->read( io_f.fileData, io_f.fileSize );

			m_strmI->close(); // Do not forget to close the file.

		} else {
			m_strmStatus = getStrmStatus( m_strmI );
		}

		return successInit;
	}

	StrmRdr::IOErrors StrmRdr::getStrmStatus( std::ios* p_strm ) {
		StrmRdr::IOErrors ioErrors = IOErrors_NA;
		if( p_strm->eof() ) {
			ioErrors = IOErrors_EOF;
		} else if( p_strm->bad() ) {
			ioErrors = IOErrors_BAD;
		} else if( p_strm->fail() ) {
			ioErrors = IOErrors_FAIL;
		}
		return ioErrors;
	}
}