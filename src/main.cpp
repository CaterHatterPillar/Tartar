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
	
	std::string tarName = "../demo.tar";
	Tartar::Tarchive* tartar = new Tartar::Tarchive(tarName.c_str());
	successDemo = tartar->init(); // Call me to initialize tar archive.
	if( successDemo==true ) {
		for( unsigned int i = 0; i<5 && successDemo==true; i++ ) {
			std::string demoFile = demoFiles[i];
			successDemo = tartar->tarchiveFile( demoFile.c_str() );
		}
		if( successDemo==true ) {
			tartar->done(); // Call me to close tar archive.
		}
	}

	delete tartar;
	return (int)!successDemo;
}