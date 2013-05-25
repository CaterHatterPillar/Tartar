#ifndef TARTAR_USTAR_H
#define TARTAR_USTAR_H

typedef char byte;

#include <cstring> // memset

namespace Tartar {
	//u s t a r \0 0 0 at byte 257 ("ustar" followed by a null byte followed by two digits '0', 8 bytes in total) [Wikipedia]
	static const char* g_UStar_Indicator = "ustar  ";
	static const unsigned int g_UStar_Size = 512;

	struct UStar {
		// POSIX.1-1988:
		const static unsigned sFilename		= 100;	byte filename	[sFilename	];	// File name.
		const static unsigned sFileMode		= 8;	byte fileMode	[sFileMode	];	// File mode.
		const static unsigned sIDNumUser	= 8;	byte idNumUser	[sIDNumUser	];	// Owners numeric user ID.
		const static unsigned sIDNumGroup	= 8;	byte idNumGroup	[sIDNumGroup];	// Groups numeric user ID.
		const static unsigned sFileSize		= 12;	byte fileSize	[sFileSize	];	// File size in bytes.
		const static unsigned sModified		= 12;	byte modified	[sModified	];	// Last modification time in numeric Unix time format.
		const static unsigned sChecksum		= 8;	byte checksum	[sChecksum	];	// Checksum for header record.
		const static unsigned sLinkIctr		= 1;	byte linkIctr	[sLinkIctr	];	// Link indicator (file type).
		const static unsigned sLinkName		= 100;	byte linkName	[sLinkName	];	// Name of linked file.

		// POSIX IEEE P1003.1:
		const static unsigned sUStarIctr	= 6;	byte ustarIctr	[sUStarIctr	];	// UStar indicator "ustar".
		const static unsigned sUStarVsn		= 2;	byte ustarVsn	[sUStarVsn	];	// UStar version "00".
		const static unsigned sIDUser		= 32;	byte idUser		[sIDUser	];	// Owner user-name.
		const static unsigned sIDGroup		= 32;	byte idGroup	[sIDGroup	];	// Owner group-name.
		const static unsigned sDevNumMaj	= 8;	byte devNumMaj	[sDevNumMaj	];	// Device major number.
		const static unsigned sDevNumMin	= 8;	byte devNumMin	[sDevNumMin	];	// Device minor number.
		const static unsigned sFilePfix		= 155;	byte filePfix	[sFilePfix	];	// Filename prefix.

		// The header is padded with NUL bytes to make it fill a 512 byte record. [Wikipedia]
		const static unsigned sPad			= 12;	byte pad		[sPad		];

		UStar() {
			std::memset( this, 0, sizeof(UStar) );
		}
		~UStar() {
			// Do nothing.
		}
	};

	// *********************
	// Link indicator field:
	// *********************
	// POSIX.1-1988:
	static const unsigned int g_UStar_LinkIndicator_Normal		= 0;
	static const unsigned int g_UStar_LinkIndicator_Hard		= 1;
	static const unsigned int g_UStar_LinkIndicator_Symbolic	= 2;
	// POSIX IEEE P1003.1:
	// | 3		- Character special
	// | 4		- Block special
	// | 5		- Directory
	// | 6		- FIFO
	// | 7		- Contiguous file
	// | g		- Global extended header with meta data (POSIX.1-2001)
	// | x		- Extended header with meta data for the next file in the archive (POSIX.1-2001)
	// | A–Z	- Vendor specific extensions (POSIX.1-1988)
	// *********************
}

// http://en.wikipedia.org/wiki/Tar_%28computing%29
// Retrieved 23-05-2013.

#endif //TARTAR_USTAR_H