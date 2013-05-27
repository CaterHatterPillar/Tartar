#include <string>

#include <Tartar.h>

//Temp
#include <Windows.h>
#include <stdio.h>
#include <iostream>

// Demo
int main() {
	bool successDemo = false;

	// Mem demo:
	AllocConsole(); //Temp
	
	std::string demo = "I wish to be formatted into a tar-archive";
	std::string demo2 = "I too wish to be formatted into a tar-archive, only better.";
	Tartar::File f;
	Tartar::TarCookMem* tarChef = new Tartar::TarCookMem( f );
	tarChef->cook( "demo.demo", demo.c_str(), demo.size() );
	tarChef->cook( "demo2.demo", demo2.c_str(), demo2.size() );
	
	char* p = f.fileData;
	for( unsigned int i = 0; i < f.fileSize; i++ )
	{
		std::cout << *p;
		p++;
	}

	// File Demo:
	/*
	std::string demoFiles[5];
	demoFiles[0] = "../demo1.txt";
	demoFiles[1] = "../demo2.txt";
	demoFiles[2] = "../demo3.txt";
	demoFiles[3] = "../demo4.txt";
	demoFiles[4] = "../demo5.txt";
	
	std::string tarName = "../demo.tar";
	Tartar::TarCookFile* tarCook = new Tartar::TarCookFile(tarName.c_str());
	successDemo = tarCook->init(); // Call me to initialize tar archive.
	if( successDemo==true ) {
		for( unsigned int i = 0; i<5 && successDemo==true; i++ ) {
			std::string demoFile = demoFiles[i];
			successDemo = tarCook->cookFile( demoFile.c_str() );
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
	*/

	return (int)!successDemo;
}