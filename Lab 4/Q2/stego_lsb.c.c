#include <stdio.h>
#include <stdlib.h>

#define WIDTH 512
#define HEIGHT 512

// Function to read a PGM image in text format.
// 'pixels' stores the pixel values of the image specified by 'filename'.
int readPGMText(const char *filename, unsigned char *pixels, int width, int height) {
}

// Function to write a PGM image in text format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename'.
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
}


// Function to write a PGM image in binary format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename' in binary format.

int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height) {
}

// Function to hide a secret image using the 4-bit LSB steganography algorithm.
// The dereferenced values of 'coverPixels' (cover image) are updated with the dereferenced values of 
// 'secretPixels' (secret image) based on the 4-bit LSB steganography algorithm

void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {

}

// Function to extract the secret image using 4-LSB steganography algorithm.
// The extracted pixel values, derived from the stego image referenced by 'coverPixels',
// are stored in the memory space pointed to by 'outputPixels' 
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {

}

int main() {
    char cover_image[]="baboon.pgm";
    char secret_image[]="farm.pgm";
    char stego_image[]="stego_image_bin.pgm";
    char extracted_secret[]="extracted_secret.pgm";
    

    unsigned char *coverPixels, *secretPixels, *outputPixels;
    int coverWidth=WIDTH, coverHeight=HEIGHT, secretWidth=WIDTH, secretHeight=HEIGHT;

    // Using malloc, dynnamically request extact memory space,referenced by coverPixels, to store the cover image pixel values. 
	
    // Read the cover image file (text PGM) and store its pixels in 'coverPixels' referenced memory space.

    //  Using malloc, dynamically request extact memory space, referenced by 'secretPixels', to store the secret image pixel values.
    
    // Read the secret image file (text PGM) and store its pixels in 'secretPixels' referenced memory space.

    // Check if the dimensions of both images match, exit if they don't.
 
    // Call the function embedLSB to embed the secret image into the cover image.
    
    // The stego image pixels are stored in 'coverPixels' referenced memory space.
        
    // Save the stego image into binary format to stego_image_bin.pgm
  
    //  Using malloc, dynamically request exact memory space, referenced by 'outputPixels', to store the extracted secret image    

    // Call the function extractLSB to extract the secret image from the stego image
    
    // Save the extracted secret image in a text format to extracted_secret.pgm

   
    return 0;
}

