#include <Strm.h>

namespace Tartar {
	Strm::Strm( const char* p_filepath ) : m_filepath( p_filepath ) {
		m_strmStatus = IOErrors_NA;
	}
	Strm::~Strm() {
		// Do nothing.
	}

	void Strm::setStrmStatus( std::ios* p_strm ) {
		m_strmStatus = getStrmStatus( p_strm );
	}

	Strm::IOErrors Strm::getStrmStatus( std::ios* p_strm ) {
		Strm::IOErrors ioErrors = IOErrors_NA;
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