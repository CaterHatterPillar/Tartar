#ifndef TARTAR_TARCHIVE_H
#define TARTAR_TARCHIVE_H

// Creates a tar-archive.

namespace Tartar {
	struct UStar;

	class StrmWtr;
}

namespace Tartar {
	enum PrevErrors {
		PrevErrors_NA,
		PrevErrors_UNEXPECTED_HEADER_SIZE,
		PrevErrors_UNKNOWN_INPUT,
		PrevErrors_UNKNOWN_OUTPUT
	};

	class Tarchive {
	public:
		Tarchive( const char* p_tarName );
		~Tarchive();

		bool init();
		void done();

		bool tarchiveFile( const char* p_filename );

		PrevErrors getPrevRecordedError() { return m_prevError; }
	protected:
	private:
		bool initHdr( UStar& io_hdr, const char* p_fileName, unsigned long p_fileSize );
		unsigned int calcChecksumHdr( UStar* p_hdr );
		void tarchive( UStar& p_hdr, const char* p_data, unsigned long p_dataSize );

		const char* m_tarName;
		PrevErrors m_prevError;
		StrmWtr* m_strmTar;
	};
}

#endif //TARTAR_TARCHIVE_H