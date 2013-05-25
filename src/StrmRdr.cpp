#include <fstream>

#include <Strm.h>
#include <StrmRdr.h>

namespace Tartar {
	StrmRdr::StrmRdr( const char* p_filepath ) : Strm( p_filepath ) {
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
			io_f.fileSize = (unsigned long)m_strmI->tellg();
			m_strmI->seekg( 0, std::ios::beg );

			// Get contents of file:
			io_f.fileData = new char[ io_f.fileSize ];
			m_strmI->read( io_f.fileData, io_f.fileSize );

			m_strmI->close(); // Do not forget to close the file.

		} else {
			setStrmStatus( m_strmI );
		}

		return successInit;
	}
}