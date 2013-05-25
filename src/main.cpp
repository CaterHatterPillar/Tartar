#include <string>

#include <Tartar.h>

// Demo
int main() {
	bool successDemo = false;

	std::string demoFiles[5];
	demoFiles[0] = "../demo1.txt";
	demoFiles[1] = "../demo2.txt";
	demoFiles[2] = "../demo3.txt";
	demoFiles[3] = "../demo4.txt";
	demoFiles[4] = "../demo5.txt";
	
	// Cook.
	std::string tarName = "../demo.tar";
	Tartar::TarCook* tarCook = new Tartar::TarCook(tarName.c_str());
	successDemo = tarCook->init(); // Call me to initialize tar archive.
	if( successDemo==true ) {
		for( unsigned int i = 0; i<5 && successDemo==true; i++ ) {
			std::string demoFile = demoFiles[i];
			successDemo = tarCook->tarchiveFile( demoFile.c_str() );
		}
		if( successDemo==true ) {
			tarCook->done(); // Call me to close tar archive.
		}
	}

	// Uncook.
	Tartar::TarUncook* tarUncook = new Tartar::TarUncook( tarName.c_str() );
	Tartar::Tar t;
	successDemo = tarUncook->init( t );
	if( successDemo==true ) {
		// Do stuff.
	}

	delete tarCook;
	return (int)!successDemo;
}