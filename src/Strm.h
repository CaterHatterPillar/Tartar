#ifndef TARTAR_STRM_H
#define TARTAR_STRM_H

#include <fstream> // Replace me with forward decl.

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
		enum IOErrors {
			IOErrors_NA,
			IOErrors_EOF,
			IOErrors_BAD,
			IOErrors_FAIL
		};

		Strm( const char* p_filepath );
		~Strm();

		IOErrors getStatus() const { return m_strmStatus; }
	protected:
		void setStrmStatus( std::ios* p_strm );
	
		const char* m_filepath;
	private:
		IOErrors getStrmStatus( std::ios* p_strm );

		IOErrors m_strmStatus;
	};
}

#endif //TARTAR_STRM_H