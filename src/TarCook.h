#ifndef TARTAR_TARTARBASE_H
#define TARTAR_TARTARBASE_H

namespace Tartar {
	struct UStar;
}

namespace Tartar {
	enum TartarErrors {
		TartarErrors_NA,
		TartarErrors_UNEXPECTED_HEADER_SIZE,
		TartarErrors_UNKNOWN_INPUT,
		TartarErrors_UNKNOWN_OUTPUT
	};

	class TarCook {
	public:
		TarCook();
		virtual ~TarCook();

		virtual bool init();

		TartarErrors getLastError() const { return m_lastError; }
	protected:
		bool cookHdr( UStar& io_hdr, const char* p_fileName, unsigned long p_fileSize );
		unsigned int calcChecksumHdr( UStar* p_hdr );
		unsigned int getPadNum( unsigned long p_size, unsigned long p_sizeBlock );

		TartarErrors m_lastError;
	private:
	};
}

#endif //TARTAR_TARTARBASE_H