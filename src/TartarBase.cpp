#include <UStar.h>

#include <TartarBase.h>

namespace Tartar {
	TartarBase::TartarBase() {
		m_lastError = TartarErrors_NA;
	}
	TartarBase::~TartarBase() {
		// Do nothing.
	}

	bool TartarBase::init() {
		bool successInit = true;

		// Control header size.
		if( sizeof(UStar)!=g_UStar_Size ) {
			m_lastError = TartarErrors_UNEXPECTED_HEADER_SIZE;
			successInit = false;
		}

		return successInit;
	}
}