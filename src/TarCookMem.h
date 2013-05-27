#ifndef TARTAR_TARCOOKMEM_H
#define TARTAR_TARCOOKMEM_H

namespace Tartar {
	struct File;
}

#include <TarCook.h>

namespace Tartar {
	class TarCookMem : public TarCook {
	public:
		TarCookMem( File& io_f );
		~TarCookMem();

		bool init();

		bool cook( const char* p_filename, const char* p_data, unsigned long p_dataSize );
	protected:
	private:
		bool format( const char* p_filename, const char* p_data, unsigned long p_dataSize, File& io_f );

		File* m_f;

		char* m_arc; // archive
		unsigned long m_arcCnt;
	};
}

#endif //TARTAR_TARCOOKMEM_H