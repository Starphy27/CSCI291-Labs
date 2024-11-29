#include <stdio.h>      // Include the standard input-output library for file operations
#include <stdlib.h>     // Include the standard library for memory allocation functions
#include <string.h>     // Include string handling functions

#define WIDTH 512       // Define the width of the image
#define HEIGHT 512      // Define the height of the image

// Function to read a PGM image (either text or binary format).
int readPGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "r");  // Open the file in read mode
    if (!file) {  // If the file couldn't be opened, display an error and return -1
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    char header[3];  // Array to store the header (e.g., "P2" or "P5")
    int max_val;     // Variable to store the maximum pixel value (usually 255)

    // Read the header of the PGM file (P2 for text format, P5 for binary format)
    if (fscanf(file, "%s", header) != 1) {
        fprintf(stderr, "Error reading header from file %s\n", filename);
        fclose(file);
        return -1;
    }

    // Check for valid format (P2 or P5)
    if (header[0] != 'P' || (header[1] != '2' && header[1] != '5')) {
        fprintf(stderr, "Invalid PGM file format: %s\n", header);
        fclose(file);
        return -1;
    }

    // Skip comments if present
    int ch;  // Variable to hold characters while reading comments
    while ((ch = fgetc(file)) == '#') {  // Loop through comment lines
        while ((ch = fgetc(file)) != '\n' && ch != EOF);  // Skip till end of the comment line
    }
    ungetc(ch, file);  // Put back the last character so the next read works correctly

    // Read the width, height, and maximum pixel value
    fscanf(file, "%d %d %d", &width, &height, &max_val);

    // Read pixel data based on format (text or binary)
    if (header[1] == '2') {  // If the format is text-based (P2)
        for (int i = 0; i < width * height; i++) {  // Loop through all pixels
            fscanf(file, "%hhu", &pixels[i]);  // Read each pixel value
        }
    } else {  // If the format is binary-based (P5)
        fgetc(file);  // Read the newline character after the header
        fread(pixels, sizeof(unsigned char), width * height, file);  // Read pixel data as binary
    }

    fclose(file);  // Close the file after reading
    return 0;  // Return success
}

// Function to write a PGM image in text format.
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "w");  // Open the file in write mode
    if (!file) {  // If the file couldn't be opened, display an error and return -1
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    // Write header for PGM
    fprintf(file, "P2\n");  // Text format header for PGM
    fprintf(file, "%d %d\n", width, height);  // Write width and height
    fprintf(file, "255\n");  // Write the maximum pixel value

    // Write pixel data, formatted as text
    for (int i = 0; i < width * height; i++) {  // Loop through each pixel
        fprintf(file, "%d ", pixels[i]);  // Write the pixel value
        if ((i + 1) % width == 0) {  // If we've reached the end of a row
            fprintf(file, "\n");  // Start a new line
        }
    }

    fclose(file);  // Close the file after writing
    return 0;  // Return success
}

// Function to write a PGM image in binary format.
int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "wb");  // Open the file in binary write mode
    if (!file) {  // If the file couldn't be opened, display an error and return -1
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    // Write header for PGM
    fprintf(file, "P5\n");  // Binary format header for PGM
    fprintf(file, "%d %d\n", width, height);  // Write width and height
    fprintf(file, "255\n");  // Write the maximum pixel value

    // Write pixel data in binary format
    fwrite(pixels, sizeof(unsigned char), width * height, file);  // Write all pixels at once

    fclose(file);  // Close the file after writing
    return 0;  // Return success
}

// Function to hide a secret image using the 4-bit LSB steganography algorithm.
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {  // Loop through all pixels
        // Clear the last 4 bits of the cover image pixel and set the last 4 bits with the secret image pixel
        coverPixels[i] &= 0xF0;  // Keep only the upper 4 bits of the cover image pixel
        coverPixels[i] |= (secretPixels[i] >> 4);  // Store the 4 MSB of the secret image in the lower 4 bits of the cover image pixel
    }
}

// Function to extract the secret image using the 4-LSB steganography algorithm.
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {  // Loop through all pixels
        // Extract the last 4 bits of the cover image pixel
        outputPixels[i] = coverPixels[i] & 0x0F;  // Get the lower 4 bits of the cover image pixel
        outputPixels[i] <<= 4;  // Shift the extracted bits to the higher 4 bits
    }
}

int main() {
    char cover_image[] = "baboon.pgm";  // Filename for the cover image
    char secret_image[] = "farm.pgm";   // Filename for the secret image
    char stego_image[] = "stego_image_bin.pgm";  // Filename for the stego image
    char extracted_secret[] = "extracted_secret.pgm";  // Filename for the extracted secret image

    unsigned char *coverPixels, *secretPixels, *outputPixels;  // Pointers to store pixel data
    int coverWidth = WIDTH, coverHeight = HEIGHT, secretWidth = WIDTH, secretHeight = HEIGHT;  // Image dimensions

    // Dynamically allocate memory for cover and secret images
    coverPixels = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char));
    secretPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));

    if (!coverPixels || !secretPixels) {  // Check if memory allocation failed
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;  // Exit if memory allocation failed
    }

    // Read the cover and secret images
    if (readPGMText(cover_image, coverPixels, coverWidth, coverHeight) != 0) {
        free(coverPixels);  // Free memory if reading the cover image fails
        free(secretPixels);  // Free memory if reading the secret image fails
        return -1;
    }

    if (readPGMText(secret_image, secretPixels, secretWidth, secretHeight) != 0) {
        free(coverPixels);  // Free memory if reading the secret image fails
        free(secretPixels);  // Free memory if reading the secret image fails
        return -1;
    }

    // Check if the dimensions match between cover and secret images
    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        fprintf(stderr, "Cover and secret images have different dimensions.\n");
        free(coverPixels);  // Free memory
        free(secretPixels);  // Free memory
        return -1;  // Exit if dimensions do not match
    }

    // Call the function embedLSB to embed the secret image into the cover image
    embedLSB(coverPixels, secretPixels, coverWidth, coverHeight);

    // Write the stego image in binary format to stego_image_bin.pgm
    if (writePGMBinary(stego_image, coverPixels, coverWidth, coverHeight) != 0) {
        free(coverPixels);  // Free memory if writing fails
        free(secretPixels);  // Free memory if writing fails
        return -1;
    }

    // Dynamically allocate memory for output pixels (extracted secret image)
    outputPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (!outputPixels) {  // Check if memory allocation failed
        fprintf(stderr, "Memory allocation failed.\n");
        free(coverPixels);  // Free memory
        free(secretPixels);  // Free memory
        return -1;
    }

    // Call the function extractLSB to extract the secret image from the stego image
    extractLSB(coverPixels, outputPixels, coverWidth, coverHeight);

    // Save the extracted secret image in a text format
    if (writePGMText(extracted_secret, outputPixels, secretWidth, secretHeight) != 0) {
        free(coverPixels);  // Free memory
        free(secretPixels);  // Free memory
        free(outputPixels);  // Free memory
        return -1;  // Exit if writing the extracted image fails
    }

    printf("Steganography complete!\n");  // Print a success message

    // Free dynamically allocated memory
    free(coverPixels);
    free(secretPixels);
    free(outputPixels);

    return 0;  // Return success
}