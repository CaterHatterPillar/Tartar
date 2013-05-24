#ifndef TARTAR_TARTAPE_H
#define TARTAR_TARTAPE_H

// Reads a tar-archive.

namespace Tartar {
	class Tartape {
	public:
		Tartape( const char* p_targetTar );
		~Tartape();

		bool init();
	protected:
	private:
		const char* m_targetTar;
	};
}

#endif // TARTAR_TARTAPE_H