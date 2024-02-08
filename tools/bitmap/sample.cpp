//Sample use

#include <iostream>
#include <string>
#include <fstream>
#include "bitmap.h"
using namespace std;

int main(){

	//Creating fstream object
	fstream *input;
	input = new fstream;

	//Opening bitmap file 
	input->open("foo.bmp", ios::binary | ios::in | ios::out);

	//Creating bitmap object using the fstream object in the constructor
	Bitmap *bar;
	bar = new Bitmap(input);

	//Printing bitmap object data
	cout << "\nFile Info:\n\n";
	cout << "Size : " << bar->getSize() << " bytes\n";
	cout << "Pixel offset : " << bar->getOffset() << " pixels\n"; 
	cout << "DIB header size: " << bar->getDIB() << " bytes\n";
	cout << "Image width: " << bar->getWidth() << " pixels\n";
	cout << "Image height: " << bar->getHeight() << " pixels\n\n";
	cout << "Total Pixels: " << bar->getArraySize() << "\n\n";

	//Changing the green value of every pixel in the bitmap object to 0
	for (int i = 0; i < bar->getArraySize()-bar->getOffset(); i++)
		bar->setPixelGreen(i,0);

	//Creating new fstream object 
	fstream *output;
	output = new fstream;

	//Opening output file
	output->open("baz.bmp", ios::binary | ios::in | ios::out | ios::trunc);


	//Writing the edited .bmp file to the output file
	bar->writeToFile(output);

	//Closing file streams
	input->close();
	output->close();

	return 0;

}