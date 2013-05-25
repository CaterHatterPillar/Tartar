#ifndef TARTAR_TAR_H
#define TARTAR_TAR_H

#include <vector>

namespace Tartar {
	struct File {
		unsigned long fileSize;
		char* fileData;

		File() {
			std::memset( this, 0, sizeof(File) );
		}
		~File() {
			if( fileData!=0 ) {
				delete[] fileData;
			}
		}
	};

	struct Tar {
		std::vector<File> files;

		Tar() {
			files = std::vector<File>();
		}
		~Tar() {
			// Do nothing.
		}
	};
}

#endif //TARTAR_TAR_H