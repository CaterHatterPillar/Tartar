#include <StrmWtr.h>

namespace Tartar {
	StrmWtr::StrmWtr( const char* p_filepath ) : Strm( p_filepath ) {
		m_strmO = nullptr;
	}
	StrmWtr::~StrmWtr() {
		if( m_strmO!=nullptr ) {
			if( m_strmO->is_open()==true ) {
				m_strmO->close();
			}
			delete m_strmO;
		}
	}

	bool StrmWtr::init() {
		bool successInit = false;

		m_strmO = new std::ofstream();
		m_strmO->open( m_filepath, std::ios::out );
		if( m_strmO->is_open() ) {
			successInit = true;
		} else {
			setStrmStatus( m_strmO );
		}

		return successInit;
	}
	void StrmWtr::done() {
		if( m_strmO!=nullptr ) {
			if( m_strmO->is_open() ) {
				m_strmO->close();
			}
		}
	}

	void StrmWtr::push( const char* p_fileData, unsigned long p_fileSize ) {
		m_strmO->write( p_fileData, p_fileSize );
	}
}