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

	unsigned int TartarBase::calcChecksumHdr( UStar* p_hdr ) {
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
}