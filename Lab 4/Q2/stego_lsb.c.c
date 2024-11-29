#include <stdio.h>
#include <stdlib.h>

#define WIDTH 512
#define HEIGHT 512

// Function to read a PGM image in text format.
// 'pixels' stores the pixel values of the image specified by 'filename'.
int readPGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    char header[3];
    int max_val;

    // Read the header of the PGM file (P2)
    if (fscanf(file, "%s", header) != 1 || header[0] != 'P' || header[1] != '2') {
        fprintf(stderr, "Invalid PGM file format\n");
        fclose(file);
        return -1;
    }

    // Skip comments
    while (fgetc(file) == '#') {
        while (fgetc(file) != '\n');
    }

    // Read width, height, and max pixel value
    fscanf(file, "%d %d %d", &width, &height, &max_val);

    // Read pixel data
    for (int i = 0; i < width * height; i++) {
        fscanf(file, "%hhu", &pixels[i]);
    }

    fclose(file);
    return 0;
}

// Function to write a PGM image in text format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename'.
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    // Write PGM header
    fprintf(file, "P2\n");
    fprintf(file, "# Created by Steganography\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");

    // Write pixel data
    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d ", pixels[i]);
        if ((i + 1) % width == 0) fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

// Function to write a PGM image in binary format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename' in binary format.
int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    // Write PGM header
    fprintf(file, "P5\n");
    fprintf(file, "# Created by Steganography\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");

    // Write pixel data
    fwrite(pixels, sizeof(unsigned char), width * height, file);

    fclose(file);
    return 0;
}

// Function to hide a secret image using the 4-bit LSB steganography algorithm.
// The dereferenced values of 'coverPixels' (cover image) are updated with the dereferenced values of 
// 'secretPixels' (secret image) based on the 4-bit LSB steganography algorithm
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        // Extract the 4 least significant bits of the secret pixel and embed it into the 4 least significant bits of the cover pixel
        coverPixels[i] &= 0xF0;  // Clear the 4 LSB of the cover pixel
        coverPixels[i] |= (secretPixels[i] >> 4);  // Embed the top 4 bits of the secret pixel into the cover pixel
    }
}

// Function to extract the secret image using 4-LSB steganography algorithm.
// The extracted pixel values, derived from the stego image referenced by 'coverPixels',
// are stored in the memory space pointed to by 'outputPixels' 
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        // Extract the 4 least significant bits from the cover image
        outputPixels[i] = (coverPixels[i] & 0x0F) << 4;  // Shift the 4 LSB to the top 4 bits of the secret pixel
    }
}

int main() {
    char cover_image[] = "baboon.pgm";
    char secret_image[] = "farm.pgm";
    char stego_image[] = "stego_image_bin.pgm";
    char extracted_secret[] = "extracted_secret.pgm";

    unsigned char *coverPixels, *secretPixels, *outputPixels;
    int coverWidth = WIDTH, coverHeight = HEIGHT, secretWidth = WIDTH, secretHeight = HEIGHT;

    // Using malloc, dynamically request memory space, referenced by coverPixels, to store the cover image pixel values.
    coverPixels = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char));
    if (!coverPixels) {
        fprintf(stderr, "Memory allocation failed for cover image\n");
        return -1;
    }

    // Read the cover image file (text PGM) and store its pixels in 'coverPixels' referenced memory space.
    if (readPGMText(cover_image, coverPixels, coverWidth, coverHeight) != 0) {
        free(coverPixels);
        return -1;
    }

    // Using malloc, dynamically request memory space, referenced by 'secretPixels', to store the secret image pixel values.
    secretPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (!secretPixels) {
        fprintf(stderr, "Memory allocation failed for secret image\n");
        free(coverPixels);
        return -1;
    }

    // Read the secret image file (text PGM) and store its pixels in 'secretPixels' referenced memory space.
    if (readPGMText(secret_image, secretPixels, secretWidth, secretHeight) != 0) {
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Check if the dimensions of both images match, exit if they don't.
    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        fprintf(stderr, "Error: Cover and secret images have different dimensions\n");
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Call the function embedLSB to embed the secret image into the cover image.
    embedLSB(coverPixels, secretPixels, coverWidth, coverHeight);

    // The stego image pixels are stored in 'coverPixels' referenced memory space.
    // Save the stego image into binary format to stego_image_bin.pgm.
    if (writePGMBinary(stego_image, coverPixels, coverWidth, coverHeight) != 0) {
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Using malloc, dynamically request memory space, referenced by 'outputPixels', to store the extracted secret image.
    outputPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (!outputPixels) {
        fprintf(stderr, "Memory allocation failed for extracted secret image\n");
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Call the function extractLSB to extract the secret image from the stego image.
    extractLSB(coverPixels, outputPixels, coverWidth, coverHeight);

    // Save the extracted secret image in a text format to extracted_secret.pgm.
    if (writePGMText(extracted_secret, outputPixels, secretWidth, secretHeight) != 0) {
        free(coverPixels);
        free(secretPixels);
        free(outputPixels);
        return -1;
    }

    // Free dynamically allocated memory.
    free(coverPixels);
    free(secretPixels);
    free(outputPixels);

    return 0;
}