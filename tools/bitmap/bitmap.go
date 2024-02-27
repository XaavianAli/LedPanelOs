package main

import (
	//"bufio"
	"fmt"
	//"io"
	"os"
	//"math"
	"encoding/binary"
)

type pixel struct {
	Red   byte
	Blue  byte
	Green byte
}

type Bitmap struct {
	Size        int16 //Are these all apropriate data types? 
	Offset      int16
	DIB         int16
	Width       int16
	Height      int16
	Padding     int
	ArraySize   int
	HeaderArray []byte
	pixelArray  [][]pixel // Honestly, probably better than original implementation of 1D array
}

func LoadBitmap(filePath string) (*Bitmap, error) {
	b := new(Bitmap)

	input, err := os.ReadFile(filePath) // Whole file into memory at once, I dont care tbh if you load a 50GB file into memory that's on you
	if err != nil {
		return nil, err
	}

	if input[0] != byte('B') && input[1] != byte('M') {
		return nil, fmt.Errorf("Invalid file type: %s, are you sure it's a .bmp file?", filePath)
	}

	// Wow shout out Golang
	b.Size = int16(binary.LittleEndian.Uint16(input[2:6]))
	b.Offset = int16(binary.LittleEndian.Uint16(input[10:14]))
	b.DIB = int16(binary.LittleEndian.Uint16(input[14:18]))
	b.Width = int16(binary.LittleEndian.Uint16(input[18:22]))
	b.Height = int16(binary.LittleEndian.Uint16(input[22:26]))
	b.Padding = int((4-((b.Width*3)%4))%4) // Ugly af don't ask me how I came up with this
	b.ArraySize = int(b.Offset + ((b.Width * int16(b.Padding)) * b.Height)) // Go type casting is lowkey cursed

	return b, nil
}

func (b *Bitmap) WriteBitmap(filePath string) error {
	fmt.Printf("Uhh wrote bitmap to file w size %d\n", b.Size)
	return nil
}

func main() {
	x, err := LoadBitmap("./red.bmp")
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(x)
	x.WriteBitmap("FakePath")
}
