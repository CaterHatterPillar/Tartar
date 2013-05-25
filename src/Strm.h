#ifndef TARTAR_STRM_H
#define TARTAR_STRM_H

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

	class Strm {
	public:
		Strm()	{}	// Temp
		~Strm() {}	// Temp
	protected:
	private:
	};
}

#endif //TARTAR_STRM_H