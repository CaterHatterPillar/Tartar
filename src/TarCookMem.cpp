#include <cstring> // memcpy

#include <Tar.h>
#include <UStar.h>

#include <TarCookMem.h>

namespace Tartar {
	TarCookMem::TarCookMem( File& io_f ) : TarCook() {
		m_f = &io_f;

		m_arc = nullptr;
		m_arcCnt = 0;
	}
	TarCookMem::~TarCookMem() {
		// Do nothing.
	}

	bool TarCookMem::init() {
		bool successInit = TarCook::init();
		return successInit;
	}

	bool TarCookMem::cook( const char* p_filename, const char* p_data, unsigned long p_dataSize ) {
		bool okCook = false;

		// Begin by formatting the data into tar-format:
		File f;
		okCook = format( p_filename, p_data, p_dataSize, f );
		if( okCook==true ) {
			char* arc = nullptr;
			unsigned long arcCnt = 0;
			
			// If already existing arhive, copy data to temp archive:
			if( m_arcCnt > 0 ) {
				arc = new char[ m_arcCnt ];
				std::memcpy( arc, m_arc, m_arcCnt );

				arcCnt = m_arcCnt;
				m_arcCnt = 0;

				delete[] m_arc;
				m_arc = nullptr;
			}

			m_arcCnt = arcCnt + f.fileSize;
			m_arc = new char[ m_arcCnt ];

			char* p = m_arc;
			std::memcpy( p, arc, arcCnt ); // Copy original archive.
			p += arcCnt;
			std::memcpy( p, f.fileData, f.fileSize );

			m_f->fileData = m_arc;
			m_f->fileSize = m_arcCnt;

			delete[] arc;
		}

		return okCook;
	}

	bool TarCookMem::format( const char* p_filename, const char* p_data, unsigned long p_dataSize, File& io_f ) {
		UStar hdr;
		bool okFormat = cookHdr( hdr, p_filename, p_dataSize );
		if(okFormat) {
			unsigned int padNum = getPadNum( p_dataSize, sizeof(UStar));
			io_f.fileSize = sizeof(UStar) + p_dataSize + padNum;

			// Write header and data to new archive.
			io_f.fileData = new char[ io_f.fileSize ];
			//std::memset(io_f.fileData, 0, io_f.fileSize);
			char* p = io_f.fileData;
			std::memcpy( p, &hdr, sizeof(UStar) );
			p += sizeof(UStar);
			std::memcpy( p, p_data, p_dataSize );
			p += p_dataSize;

			// Pad archive:
			char nullChar = '\0';
			for( unsigned int i = 0; i < padNum; i++ ) {
				*p = nullChar;
				p++;
			}
		}

		return okFormat;
	}
}