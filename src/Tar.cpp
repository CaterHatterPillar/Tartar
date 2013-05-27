#include <Tar.h>

namespace Tartar {
	Tar::Tar() {
		m_files = std::vector<File*>();
	}
	Tar::~Tar() {
		// Do nothing.
	}

	void Tar::push( unsigned long p_fileSize, char* p_fileData ) {
		m_files.push_back( new File( p_fileSize, p_fileData ) );
	}
}