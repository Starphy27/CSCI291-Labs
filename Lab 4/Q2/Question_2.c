#include <stdio.h>  // Standard input/output functions
#include <stdlib.h> // Standard library functions, including dynamic memory allocation

#define WIDTH 512    // Define constant for image width
#define HEIGHT 512   // Define constant for image height

// Function to read a PGM image in text format
int readPGMText(const char *filename, unsigned char **pixels, int *width, int *height) {
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (!file) { // Check if file opening failed
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 0; // Return failure
    }

    char format[3];
    if (fscanf(file, "%2s", format) != 1 || format[0] != 'P' || format[1] != '2') { 
        // Check if format is valid PGM (P2)
        fclose(file);
        fprintf(stderr, "Error: Invalid PGM format\n");
        return 0;
    }

    // Skip comments in the file
    int maxGray;
    do {
        char c = fgetc(file); // Read one character
        if (c == '#') { // If it's a comment line
            while (fgetc(file) != '\n'); // Skip the comment line
        } else {
            ungetc(c, file); // Push back the character if not a comment
            break;
        }
    } while (1);

    // Read image width, height, and max gray value
    if (fscanf(file, "%d %d %d", width, height, &maxGray) != 3) {
        fclose(file);
        fprintf(stderr, "Error: Invalid image header\n");
        return 0;
    }

    // Allocate memory for pixel data
    *pixels = malloc((*width) * (*height) * sizeof(unsigned char));
    if (!*pixels) { // Check if memory allocation failed
        fclose(file);
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 0;
    }

    // Read pixel values from the file
    unsigned char *ptr = *pixels;
    for (int i = 0; i < (*width) * (*height); i++) {
        int pixelValue;
        if (fscanf(file, "%d", &pixelValue) != 1) {
            // Free memory and close file on failure
            free(*pixels);
            fclose(file);
            fprintf(stderr, "Error: Pixel reading failed\n");
            return 0;
        }
        *ptr++ = (unsigned char)pixelValue; // Store pixel value
    }

    fclose(file); // Close the file
    return 1; // Return success
}

// Function to write a PGM image in text format
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "w"); // Open the file in write mode
    if (!file) { // Check if file opening failed
        fprintf(stderr, "Error: Cannot create file %s\n", filename);
        return 0;
    }

    // Write PGM header
    fprintf(file, "P2\n%d %d\n255\n", width, height);

    // Write pixel values to the file
    unsigned char *ptr = pixels;
    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d\n", *ptr++); // Write pixel value
    }

    fclose(file); // Close the file
    return 1; // Return success
}

// Function to embed a secret image using 4-bit LSB steganography
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    unsigned char *cover = coverPixels; // Pointer to cover image pixels
    unsigned char *secret = secretPixels; // Pointer to secret image pixels

    for (int i = 0; i < width * height; i++) {
        *cover = (*cover & 0xF0) | ((*secret & 0xF0) >> 4); 
        // Embed 4 MSBs of secret into 4 LSBs of cover
        cover++;
        secret++;
    }
}

// Function to extract the secret image using 4-bit LSB steganography
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    unsigned char *cover = coverPixels; // Pointer to cover image pixels
    unsigned char *output = outputPixels; // Pointer to output image pixels

    for (int i = 0; i < width * height; i++) {
        *output = (*cover & 0x0F) << 4; // Extract 4 LSBs and shift left
        cover++;
        output++;
    }
}

int main() {
    unsigned char *coverPixels = NULL, *secretPixels = NULL, *outputPixels = NULL; // Pointers for pixel data
    int coverWidth, coverHeight, secretWidth, secretHeight; // Image dimensions

    // Read cover image
    if (!readPGMText("baboon.pgm", &coverPixels, &coverWidth, &coverHeight)) {
        fprintf(stderr, "Failed to read cover image\n");
        return 1; // Exit on failure
    }

    // Read secret image
    if (!readPGMText("farm.pgm", &secretPixels, &secretWidth, &secretHeight)) {
        free(coverPixels); // Free cover image memory
        fprintf(stderr, "Failed to read secret image\n");
        return 1;
    }

    // Check if dimensions match
    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        free(coverPixels);
        free(secretPixels);
        fprintf(stderr, "Image dimensions do not match\n");
        return 1;
    }

    // Allocate memory for output image
    outputPixels = malloc(coverWidth * coverHeight * sizeof(unsigned char));
    if (!outputPixels) { // Check if memory allocation failed
        free(coverPixels);
        free(secretPixels);
        fprintf(stderr, "Error: Memory allocation failed for outputPixels\n");
        return 1;
    }

    // Embed secret image into cover image
    embedLSB(coverPixels, secretPixels, coverWidth, coverHeight);

    // Write stego image (cover image with secret embedded)
    if (!writePGMText("stego_image.pgm", coverPixels, coverWidth, coverHeight)) {
        free(coverPixels);
        free(secretPixels);
        free(outputPixels);
        fprintf(stderr, "Failed to write stego image\n");
        return 1;
    }

    // Extract secret image from stego image
    extractLSB(coverPixels, outputPixels, coverWidth, coverHeight);

    // Write the extracted secret image to a file
    if (!writePGMText("extracted_secret.pgm", outputPixels, coverWidth, coverHeight)) {
        free(coverPixels);
        free(secretPixels);
        free(outputPixels);
        fprintf(stderr, "Failed to write extracted secret image\n");
        return 1;
    }

    // Free all dynamically allocated memory
    free(coverPixels);
    free(secretPixels);
    free(outputPixels);

    printf("Steganography process completed successfully\n");
    return 0; // Return success
}