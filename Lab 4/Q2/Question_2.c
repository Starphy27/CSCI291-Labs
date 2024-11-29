#include <stdio.h> // Standard I/O library for reading and writing
#include <stdlib.h> // Standard library for memory management

#define IMAGE_WIDTH 512 // Width of the image (in pixels)
#define IMAGE_HEIGHT 512 // Height of the image (in pixels)

// Reads pixel data from a PGM file in text format (P2)
int loadPGM(const char *filename, unsigned char *imageData, int imageWidth, int imageHeight) {
    FILE *file = fopen(filename, "r"); // Open the PGM file in read mode
    if (!file) { // If the file cannot be opened
        printf("Error: Unable to open file %s\n", filename); // Print an error message
        return -1; // Return an error code
    }

    char fileFormat[3]; // Buffer for storing the file format
    fscanf(file, "%s\n", fileFormat); // Read the format (e.g., P2)
    if (fileFormat[0] != 'P' || fileFormat[1] != '2') { // Check if the format is "P2"
        printf("Error: Invalid PGM format (Expected P2)\n"); // Print an error message if format is incorrect
        fclose(file); // Close the file
        return -2; // Return an error code
    }

    char ch = getc(file); // Read the first character to check for comments
    while (ch == '#') { // If it's a comment, skip the entire comment line
        while (getc(file) != '\n'); // Skip until the end of the line
        ch = getc(file); // Get the next character
    }
    ungetc(ch, file); // Put the character back in the file for further reading

    // Read image dimensions and max pixel value
    int width, height, maxPixelValue;
    fscanf(file, "%d %d\n%d\n", &width, &height, &maxPixelValue); // Read width, height, and max pixel value
    if (width != imageWidth || height != imageHeight) { // Check if dimensions match
        printf("Error: Image dimensions do not match\n"); // Print an error message if they don't
        fclose(file); // Close the file
        return -3; // Return an error code
    }

    // Read pixel values
    for (int i = 0; i < width * height; i++) {
        int pixelValue;
        fscanf(file, "%d", &pixelValue); // Read pixel value
        imageData[i] = (unsigned char)pixelValue; // Store it in the image data array
    }

    fclose(file); // Close the file
    return 0; // Return success code
}

// Writes pixel data to a PGM file in text format (P2)
int savePGM(const char *filename, unsigned char *imageData, int imageWidth, int imageHeight) {
    FILE *file = fopen(filename, "w"); // Open the file in write mode
    if (!file) { // If the file cannot be created
        printf("Error: Unable to create file %s\n", filename); // Print an error message
        return -1; // Return an error code
    }

    // Write header information
    fprintf(file, "P2\n"); // PGM format
    fprintf(file, "# Generated using LSB Steganography\n"); // Comment line
    fprintf(file, "%d %d\n", imageWidth, imageHeight); // Write image dimensions
    fprintf(file, "255\n"); // Write max pixel value

    // Write pixel data
    for (int i = 0; i < imageWidth * imageHeight; i++) {
        fprintf(file, "%d", imageData[i]); // Write each pixel value
        if ((i + 1) % imageWidth == 0) // Check if the end of the row is reached
            fprintf(file, "\n"); // Add a newline after each row
        else
            fprintf(file, " "); // Otherwise, add a space between pixels
    }

    fclose(file); // Close the file
    return 0; // Return success code
}

// Writes pixel data to a PGM file in binary format (P5)
int savePGMBinary(const char *filename, unsigned char *imageData, int imageWidth, int imageHeight) {
    FILE *file = fopen(filename, "wb"); // Open the file in binary write mode
    if (!file) { // If the file cannot be created
        printf("Error: Unable to create file %s\n", filename); // Print an error message
        return -1; // Return an error code
    }

    // Write header information
    fprintf(file, "P5\n"); // PGM binary format
    fprintf(file, "# Created using LSB Steganography\n"); // Comment line
    fprintf(file, "%d %d\n", imageWidth, imageHeight); // Write image dimensions
    fprintf(file, "255\n"); // Write max pixel value

    // Write pixel data in binary format
    fwrite(imageData, sizeof(unsigned char), imageWidth * imageHeight, file); // Write pixel values

    fclose(file); // Close the file
    return 0; // Return success code
}

// Embeds secret image data into the cover image using the Least Significant Bit (LSB) technique
void embedSecretData(unsigned char *coverImage, unsigned char *secretImage, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        coverImage[i] &= 0xF0; // Clear the 4 least significant bits of the cover image pixel
        unsigned char secretData = (secretImage[i] & 0xF0) >> 4; // Extract the 4 most significant bits of the secret image pixel
        coverImage[i] |= secretData; // Embed the secret data into the cover image pixel
    }
}

// Extracts the secret image data from the stego image using the LSB technique
void extractSecretData(unsigned char *stegoImage, unsigned char *extractedImage, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        unsigned char lsbData = stegoImage[i] & 0x0F; // Extract the 4 least significant bits of the stego image pixel
        extractedImage[i] = lsbData << 4; // Shift the bits to the most significant bits of the new pixel
    }
}

// Main function for executing the steganography process
int main() {
    const char *coverImageFile = "baboon.pgm"; // Cover image file name
    const char *secretImageFile = "farm.pgm"; // Secret image file name
    const char *stegoImageFile = "stego_image_bin.pgm"; // Output stego image file name
    const char *extractedSecretFile = "extracted_secret.pgm"; // Output file for extracted secret image

    unsigned char *coverImage, *secretImage, *extractedImage; // Pointers for image data
    int coverWidth = IMAGE_WIDTH, coverHeight = IMAGE_HEIGHT; // Dimensions of cover image
    int secretWidth = IMAGE_WIDTH, secretHeight = IMAGE_HEIGHT; // Dimensions of secret image

    // Allocate memory for the image data
    coverImage = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char));
    if (!coverImage) {
        printf("Error: Memory allocation failed for cover image\n");
        return -1;
    }

    if (loadPGM(coverImageFile, coverImage, coverWidth, coverHeight) != 0) {
        free(coverImage); // Free memory if loading failed
        return -2;
    }

    secretImage = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (!secretImage) {
        printf("Error: Memory allocation failed for secret image\n");
        free(coverImage); // Free memory if allocation failed
        return -3;
    }

    if (loadPGM(secretImageFile, secretImage, secretWidth, secretHeight) != 0) {
        free(coverImage); // Free memory if loading failed
        free(secretImage);
        return -4;
    }

    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        printf("Error: Image dimensions mismatch\n");
        free(coverImage); // Free memory if dimensions do not match
        free(secretImage);
        return -5;
    }

    embedSecretData(coverImage, secretImage, coverWidth, coverHeight); // Embed secret data

    if (savePGMBinary(stegoImageFile, coverImage, coverWidth, coverHeight) != 0) {
        free(coverImage); // Free memory if saving failed
        free(secretImage);
        return -6;
    }

    extractedImage = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char));
    if (!extractedImage) {
        printf("Error: Memory allocation failed for extracted image\n");
        free(coverImage); // Free memory if allocation failed
        free(secretImage);
        return -7;
    }

    extractSecretData(coverImage, extractedImage, coverWidth, coverHeight); // Extract secret data

    if (savePGM(extractedSecretFile, extractedImage, coverWidth, coverHeight) != 0) {
        free(coverImage); // Free memory if saving failed
        free(secretImage);
        free(extractedImage);
        return -8;
    }

    free(coverImage); // Free allocated memory
    free(secretImage);
    free(extractedImage);

    printf("Steganography operation completed successfully!\n"); // Print success message
    return 0; // Return success 
}
