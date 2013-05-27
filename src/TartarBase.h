#ifndef TARTAR_TARTARBASE_H
#define TARTAR_TARTARBASE_H

namespace Tartar {
	enum TartarErrors {
		TartarErrors_NA,
		TartarErrors_UNEXPECTED_HEADER_SIZE,
		TartarErrors_UNKNOWN_INPUT,
		TartarErrors_UNKNOWN_OUTPUT
	};

	class TartarBase {
	public:
		TartarBase();
		virtual ~TartarBase();

		virtual bool init();

		TartarErrors getLastError() const { return m_lastError; }
	protected:
		unsigned int calcChecksumHdr( UStar* p_hdr );

		TartarErrors m_lastError;
	private:
	};
}

#endif //TARTAR_TARTARBASE_H