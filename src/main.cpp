#include <string>

#include <Tartar.h>

// Demo
int main() {
	bool successDemo = false;
	
	std::string tarName = "demo.tar";
	Tartar::Tartar* tartar = new Tartar::Tartar(tarName.c_str());
	successDemo = tartar->init(); // Call me to initialize tar archive.
	if( successDemo==true ) {
		std::string demoFile = "../demo.txt";
		successDemo = tartar->tarchiveFile( demoFile.c_str() );
		if( successDemo==true ) {
			tartar->done(); // Call me to close tar archive.
		}
	}

	delete tartar;
	return (int)!successDemo;
}