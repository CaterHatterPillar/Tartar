#ifndef TARTAR_STRMRDR_H
#define TARTAR_STRMRDR_H

namespace std {
	typedef basic_ios<char> ios;
	typedef basic_ifstream<char> ifstream;
}

#include <Strm.h>

namespace Tartar {
	class StrmRdr {
	public:
		enum IOErrors {
			IOErrors_NA,
			IOErrors_EOF,
			IOErrors_BAD,
			IOErrors_FAIL
		};

		StrmRdr( const char* p_filepath );
		~StrmRdr();

		bool init( File& io_f );

		IOErrors getStatus() const { return m_strmStatus; }
	protected:
		IOErrors getStrmStatus( std::ios* p_strm );
	private:
		const char* m_filepath;
		
		IOErrors m_strmStatus;
		std::ifstream* m_strmI;
	};
}

#endif //TARTAR_STRMRDR_H