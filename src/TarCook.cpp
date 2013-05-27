#include <cstdio> // sprintf

#include <UStar.h>

#include <TarCook.h>

namespace Tartar {
	TarCook::TarCook() {
		m_lastError = TartarErrors_NA;
	}
	TarCook::~TarCook() {
		// Do nothing.
	}

	bool TarCook::init() {
		bool successInit = true;

		// Control header size.
		if( sizeof(UStar)!=g_UStar_Size ) {
			m_lastError = TartarErrors_UNEXPECTED_HEADER_SIZE;
			successInit = false;
		}

		return successInit;
	}

	bool TarCook::cookHdr( UStar& io_hdr, const char* p_fileName, unsigned long p_fileSize ) {
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
		// Note to self: Use octal?
		std::sprintf( io_hdr.fileSize, "%011lld",  (long long unsigned int)p_fileSize );
		// 0	- uses 0 instead of spaces. 
		// 11	- minimum number of digits to be written
		// ll	- long long unsigned
		// d	- decimal

		// Set checkum of header:
		unsigned int checksum = calcChecksumHdr( &io_hdr );
		std::sprintf( io_hdr.checksum, "%06o", checksum );

		return hdrGood;
	}

	unsigned int TarCook::calcChecksumHdr( UStar* p_hdr ) {
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

	unsigned int TarCook::getPadNum( unsigned long p_size, unsigned long p_sizeBlock ) {
		unsigned int pad = 0;
		while( (p_size%p_sizeBlock) != 0 ) {
			pad++;
			p_size++;
		}

		return pad;
	}
}