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
		File( unsigned long p_fileSize, char* p_fileData ) {
			fileSize = p_fileSize;
			fileData = p_fileData;
		}
		~File() {
			if( fileData!=0 ) {
				delete[] fileData;
			}
		}
	};

	class Tar {
	public:
		Tar();
		~Tar();

		void push( unsigned long p_fileSize, char* p_fileData );

		std::vector<File*>& getFiles() { return m_files; }
	protected:
	private:
		std::vector<File*> m_files;
	};
}

#endif //TARTAR_TAR_H