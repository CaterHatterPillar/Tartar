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

		Tartar::File f;

		m_tar = new StrmRdr( m_targetTar );
		successInit = m_tar->init( f );
		if( successInit==true ) {
			successInit = unpackTar( io_t, f );
		} else {
			// Details surrounding error may be found in StrmRdr.
			// Do error handling based off of that.
		}

		return successInit;
	}

	bool TarUncook::unpackTar( Tar& io_t, File& p_f ) {
		return false; //temp
	}
}