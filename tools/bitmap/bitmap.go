// Bitmap file format referenced from: http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
package main

import (
	//"bufio"
	"fmt"
	//"io"
	"os"
	//"math"
	"bytes"
	"encoding/binary"
)

// In RGB order even though in file they are ordered BGR for better readability 
type pixel struct { // Export? Doubt it but maybe
	Red   byte
	Green byte
	Blue  byte
}

type bitmapBase struct { // Technically Header and InfoHeader merged
	FileSize            int16 // Are these all apropriate data types? Probably not why tf were they longs in c++ implementation??? I was a silly 18 year old. Maybe use uints instead too
	Offset              int16
	DIB                 int16 // Defined in spec as "Size", and apparently should equal 40??? Am I using an old spec reference?
	Width               int16
	Height              int16
	Padding             int16 // How many zeroes are needed per line
	Planes              int16
	BitsPerPixel        int16
	Compression         int16
	CompressedImageSize int16
	XpixelsPerM         int16
	YpixelsPerM         int16
	ColorsUsed          int16
	ImportantColors     int16
	ArraySize           int16
	HeaderArray         []byte
	ColorTable          []byte    // Dont initialize if not needed (only needed if BitsPerPixel < 8)
	PixelArray          [][]pixel // Honestly, probably better than original implementation of 1D array
}

func (b *bitmapBase) Stringer() {} // Do this plz

type Bitmap24C0 struct {
	bitmapBase
}

type Bitmap interface {
	getPixelData([]byte)
	WriteBitmap(string) error
}

func (b *Bitmap24C0) getPixelData(input []byte) {
	// Load into 2d slice (Ugly) (Unreadable) (How tf do I declare slices better) (Still works tho)
	b.PixelArray = make([][]pixel, b.Width)
	for i := range b.PixelArray {
		b.PixelArray[i] = make([]pixel, b.Height)
	}
	n := b.Offset
	for i := 0; int16(i) < b.Height; i++ {
		for j := 0; int16(j) < b.Width; j++ {
			b.PixelArray[j][i].Blue = input[n]
			b.PixelArray[j][i].Green = input[n+1]
			b.PixelArray[j][i].Red = input[n+2]
			n += 3
		}
	}
}

func (b *Bitmap24C0) WriteBitmap(filePath string) error {
	_, err := os.Create(filePath)
	if err != nil {
		return err
	}
	return nil
}

func (b *bitmapBase) constructHeader(input []byte, filePath string) error {
	// Construct the header
	// Will casting from uint16 to int16 break something for large images? How does casting work? Same bits but change type or an actual conversion?
	if !bytes.Equal(input[0:2], []byte{'B','M'}) {
		return fmt.Errorf("Invalid file type: %s, are you sure it's a .bmp file?", filePath)
	}
	b.FileSize = int16(binary.LittleEndian.Uint16(input[2:6])) // Wow shout out Golang stdlib for this function
	if int(b.FileSize) != len(input) {
		return fmt.Errorf("Problem with file: %s, file size does not match header data. Is this file corrupt?", filePath)
	}
	if !bytes.Equal(input[6:10], []byte{0, 0, 0, 0}) {
		return fmt.Errorf("Problem with file: %s, file header invalid. Is this file corrupt?", filePath)
	}
	b.Offset = int16(binary.LittleEndian.Uint16(input[10:14]))
	b.DIB = int16(binary.LittleEndian.Uint16(input[14:18]))
	b.Width = int16(binary.LittleEndian.Uint16(input[18:22]))
	b.Height = int16(binary.LittleEndian.Uint16(input[22:26]))
	b.Planes = int16(binary.LittleEndian.Uint16(input[26:28]))
	b.BitsPerPixel = int16(binary.LittleEndian.Uint16(input[28:30]))
	b.Compression = int16(binary.LittleEndian.Uint16(input[30:34]))
	b.CompressedImageSize = int16(binary.LittleEndian.Uint16(input[34:38]))
	b.XpixelsPerM = int16(binary.LittleEndian.Uint16(input[38:42]))
	b.YpixelsPerM = int16(binary.LittleEndian.Uint16(input[42:46]))
	b.ColorsUsed = int16(binary.LittleEndian.Uint16(input[46:50]))
	b.ImportantColors = int16(binary.LittleEndian.Uint16(input[50:54]))
	b.Padding = int16((4 - ((b.Width * 3) % 4)) % 4) // Ugly af don't ask me how I came up with this
	b.ArraySize = b.Offset + ((b.Width + b.Padding) * b.Height)
	b.HeaderArray = input[0:b.Offset]

	return nil
}

func LoadBitmap(filePath string) (Bitmap, error) { // Chop this function up damn, single responsibility principle
	b := new(bitmapBase)

	input, err := os.ReadFile(filePath) // Whole file into memory at once, I dont care tbh if you load a 50GB file into memory that's on you
	if err != nil {
		return nil, err
	}

	if len(input) < 54 { // 54 is the minimum header size accoding to the spec
		return nil, fmt.Errorf("Invalid file: %s, is this file corrupt?", filePath)
	}

	b.constructHeader(input, filePath)
	if err != nil {
		return nil, err
	}

	// Load in some Pixel data (Color table data too if you're freaky like that)
	// Implement these eventually please
	switch b.Compression{
	case 0:
		switch b.BitsPerPixel{
		case 1:
			return nil, fmt.Errorf("Problem with file: %s, Unsupported number of bits per pixel", filePath)
		case 4:
			return nil, fmt.Errorf("Problem with file: %s, Unsupported number of bits per pixel", filePath)
		case 8:
			return nil, fmt.Errorf("Problem with file: %s, Unsupported number of bits per pixel", filePath)
		case 16:
			return nil, fmt.Errorf("Problem with file: %s, Unsupported number of bits per pixel", filePath)
		case 24:
			b := &Bitmap24C0{*b}
			b.getPixelData(input) // By the way this is fine because slices are inherently pass by reference since they're just pointers to memory
			return b, nil
		default:
			return nil, fmt.Errorf("Problem with file: %s, Unknown error, is your file corrupt or unsupported?", filePath)
		}
	case 1:
		return nil, fmt.Errorf("Problem with file: %s, Unsupported compression method", filePath)
	case 2:
		return nil, fmt.Errorf("Problem with file: %s, Unsupported compression method", filePath)
	case 3:
		return nil, fmt.Errorf("Problem with file: %s, Unsupported compression method", filePath)
	default:
		return nil, fmt.Errorf("Problem with file: %s, Unknown error, is your file corrupt or unsupported?", filePath)
	}
	
}

func main() {
	x, err := LoadBitmap("./red.bmp")
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(x)
	x.WriteBitmap("./red2.bmp")
	if err != nil {
		fmt.Println(err)
		return
	}
}
