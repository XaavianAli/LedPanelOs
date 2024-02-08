//Bitmap Header
/*

Format of BMP file (When no color space info written):
Bitmap Header (Always 14 bytes)
DIB Header (Usually 40 in my case) (BITMAPINFOHEADER)
SIZES ARE ALWAYS READ BACKWARDS
Bytes 1 & 2 are 42 and 4D in hex (B and M)
Bytes 3-6 are size of file in bytes READ BACKWARDS (ex:26 01 00 00 would read 00 00 01 26 which translates to 294)
Bytes 11-14 tell the offset of the pixel array (Where the pixel data starts)
(ex: if offset is 88, byte 89 will be the first of the pixel array)
Bytes 15-18 tells size of DIB header
Bytes 19-22 tell width in pixels
Bytes 23-26 tell height in pixels
Each pixel stores its color in 3 bytes (Red, Green, Blue)
Width bytes must be a multiple of 4, or else padded 0s will be added at the end of every line to compensate
(ex: 7 pixels wide will be 21 bytes, Three 0 bytes get added at the end to make it 24 bytes)
pixels are read from left to right, then BOTTOM TO TOP

*/


#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

class Bitmap{

	public:

		//Bitmap object Constructor. Initialized with an opened fstream object of a .bmp file
		Bitmap(fstream *input){
			// i is counter, b holds char
			int i = 1;
			char b;

			// size variables
			unsigned char s3,s2,s1,s0;

			// offset variables
			unsigned char o3,o2,o1,o0;

			// DIB variables
			unsigned char d3,d2,d1,d0;

			// width variables
			unsigned char w3,w2,w1,w0;

			// height variables
			unsigned char h3,h2,h1,h0;

			// Verifies that file is actually a bitmap and grabs header info
			try {
				while (input->get(b)){
					if (i == 1 && b != 'B')
						throw "Invalid File Type.";
					if (i == 2 && b != 'M')
						throw "Invalid File Type.";
					switch (i){
						case 3:
							s0 = b + 0;
							break;
						case 4:
							s1 = b + 0;
							break;
						case 5:
							s2 = b + 0;
							break;
						case 6:
							s3 = b + 0;
							size = (s3*pow(16,6) + s2*pow(16,4) + s1*pow(16,2) + s0);
							break;
						case 11:
							o0 = b + 0;
							break;
						case 12:
							o1 = b + 0;
							break;
						case 13:
							o2 = b + 0;
							break;
						case 14:
							o3 = b + 0;
							offset = (o3*pow(16,6) + o2*pow(16,4) + o1*pow(16,2) + o0);
							break;
						case 15:
							d0 = b + 0;
							break;
						case 16:
							d1 = b + 0;
							break;
						case 17:
							d2 = b + 0;
							break;
						case 18:
							d3 = b + 0;
							dib = (d3*pow(16,6) + d2*pow(16,4) + d1*pow(16,2) + d0);
							break;
						case 19:
							w0 = b + 0;
							break;
						case 20:
							w1 = b + 0;
							break;
						case 21:
							w2 = b + 0;
							break;
						case 22:
							w3 = b + 0;
							width = (w3*pow(16,6) + w2*pow(16,4) + w1*pow(16,2) + w0);
							padding = (4 - ((width * 3) % 4));
							if (padding == 4){
								padding = 0;
							}
							break;
						case 23:
							h0 = b + 0;
							break;
						case 24:
							h1 = b + 0;
							break;
						case 25:
							h2 = b + 0;
							break;
						case 26:
							h3 = b + 0;
							height = (h3*pow(16,6) + h2*pow(16,4) + h1*pow(16,2) + h0);
							break;
					}
					i++;
					if (i > 26)
						break;
				}
			} catch (const char* e){
				cout << "Exeption: " << e << "\n\n";
			}

			arraySize = offset + ((width + padding)*(height));

			headerArray = new unsigned char [offset];
			paddingArray = new unsigned char [height*width];
			pixelArray.resize(width*height);
			for (int i = 0; i < width*height; i++)
				pixelArray[i].resize(3);
			i = 0;
			int j = 0;
			int k = 0;
			int n = 0;

			input->clear();
			input->seekg(0, ios::beg);

			while (input->get(b)){

				if (i < offset){
					headerArray[i] = b;
				}
				
				if (i >= offset && (i-offset) % ((width*3) + padding) <= (width*3) - 1) {
					pixelArray[j][k] = b;
					k++;
				}

				if ((i-offset) % ((width*3) + padding) > (width*3) - 1 && padding != 0){
					paddingArray[n] = b;
					n++;
				}

				if (k > 2){
					k = 0;
					j++;
				}

				i++;
			}

		}

		//Returns the size of the .bmp file in bytes
		long getSize(){
			return size;
		}

		//Returns the pixel offset. (The amount of bytes in the file until the pixel data starts)
		long getOffset(){
			return offset;
		}

		//Returns the size of the DIB header in bytes
		long getDIB(){
			return dib;
		}

		//Returns the width of the bitmap image in pixels
		long getWidth(){
			return width;
		}

		//Returns the height of the bitmap image in pixels
		long getHeight(){
			return height;
		}

		//Returns the amount of padding at the end of each pixel data line
		int getPadding(){
			return padding;
		}

		//Returns the size of the pixel array, which is the size of the 
		int getArraySize(){
			return arraySize;
		}

		//Returns the specific byte at the requested header location
		unsigned char getHeaderArray(int x){
			return headerArray[x];
		}

		//Returns the specific byte at the requested 
		unsigned char getPaddingArray(int x){
			return paddingArray[x];
		}

		//Returns the value of the chosen color at the specific pixel
		unsigned char getPixelArray(int x, string s){
			if (s == "r"){
				return pixelArray[x][0];
			} else if (s == "g"){
				return pixelArray[x][1];
			} else if (s == "b"){
				return pixelArray[x][2];
			} else {
				cout << "getPixelArray(int, string): string value must be either 'r', 'g', or 'b' depending on the color. 0 has been returned.\n\n";
			}
		}

		//Sets the red value of the specified pixel
		void setPixelRed(int x, int z){
			pixelArray[x][0] = z;
		}

		//Sets the green value of the specific pixel
		void setPixelGreen(int x, int z){
			pixelArray[x][1] = z;
		}

		//Sets the blue value of the specific pixel
		void setPixelBlue(int x, int z){
			pixelArray[x][2] = z;
		}

		//Writes a bitmap object to a fstream object
		void writeToFile(fstream *output){
			int i = 0;
			int j = 0;
			int k = 0;
			int n = 0;

			while (i < size){

				if (i < offset){
					output->put(headerArray[i]);
				}

				if (i >= offset && (i-offset) % ((width*3) + padding) <= (width*3) - 1){
					output->put(pixelArray[j][k]);
					k++;
				}

				if ((i-offset) % ((width*3) + padding) > (width*3) - 1 && padding != 0){
					output->put(paddingArray[n]);
					n++;
				}

				if (k > 2){
					k = 0;
					j++;
				}

				i++;

			}
		}

		long size;
		long offset;
		long dib;
		long width;
		long height;
		int padding;
		int arraySize;
		unsigned char *headerArray;
		unsigned char *paddingArray;
		vector<vector<unsigned char>> pixelArray;

};

#endif