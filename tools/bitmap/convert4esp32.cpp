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

	string filename = "k2.bmp";

	//Opening bitmap file 
	input->open(filename, ios::binary | ios::in | ios::out);

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

    cout << "How many pixels total??? " << bar->pixelArray.size() << endl << endl;

    cout << "icon " << filename.substr(0, filename.find(".")) << " = {\n  " << bar->getHeight() << ",\n  " << bar->getWidth() << ",\n  {";
    for (int i = bar->pixelArray.size() - bar->getWidth(); i >= 0; i = i - bar->getWidth()){
        for (int j = 0; j < bar->getWidth(); j++){
            cout << "{" << (int)bar->getPixelArray(i+j, "b") << "," << (int)bar->getPixelArray(i+j, "g") << "," << (int)bar->getPixelArray(i+j, "r") << "},";
        }
    }
    cout << "}\n};" << endl;

    /*
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
    */

	return 0;

}