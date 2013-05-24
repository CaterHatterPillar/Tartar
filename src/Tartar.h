#ifndef TARTAR_TARTAR_H
#define TARTAR_TARTAR_H

namespace std {
	typedef basic_ios<char> ios;
	typedef basic_ifstream<char> ifstream;
	typedef basic_ofstream<char> ofstream;
}
namespace Tartar {
	struct UStar;
}

namespace Tartar {
	enum PrevErrors {
		PrevErrors_NA,
		PrevErrors_UNEXPECTED_HEADER_SIZE,
		PrevErrors_TAR_NOT_FOUND,
		PrevErrors_TAR_EOF,
		PrevErrors_TAR_BAD,
		PrevErrors_TAR_FAIL
	};

	class Tartar {
	public:
		Tartar( const char* p_tarName );
		~Tartar();

		bool init();
		void done();

		bool tarchiveFile( const char* p_filename );

		PrevErrors getPrevRecordedError() { return m_prevError; }
	protected:
	private:
		enum IOErrors {
			IOErrors_NA,
			IOErrors_EOF,
			IOErrors_BAD,
			IOErrors_FAIL
		};

		bool strmTarIsGood();
		IOErrors getStrmStatus( std::ios* p_strm );

		bool initHdr( UStar& io_hdr, const char* p_fileName, unsigned long p_fileSize );
		unsigned int calcChecksumHdr( UStar* p_hdr );
		void tarchive( UStar& p_hdr, const char* p_data, unsigned long p_dataSize );

		const char* m_tarName;

		PrevErrors m_prevError;

		std::ifstream* m_strmInput;
		std::ofstream* m_strmTar;
	};
}

#endif //TARTAR_TARTAR_H