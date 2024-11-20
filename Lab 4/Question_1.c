#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Function prototypes
bool is_valid_float(const char *str);
void process_file_with_fseek(const char *input_file, const char *output_file);

int main() {
    const char *input_file = "data.txt";       // Input file
    const char *output_file = "valid_data.txt"; // Output file for valid floats

    // Process the file using fseek
    process_file_with_fseek(input_file, output_file);

    return 0;
}



// Function to process the input file and write valid floats to the output file
void process_file_with_fseek(const char *input_file, const char *output_file) {
    FILE *in_file = fopen(input_file, "r");
    FILE *out_file = fopen(output_file, "w");
    if (in_file == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    if (out_file == NULL) {
        perror("Error opening output file");
        fclose(in_file);
        exit(EXIT_FAILURE);
    }

    // Determine the file size using fseek
    fseek(in_file, 0, SEEK_END);
    long file_size = ftell(in_file); // Get current file position (end of file)
    fseek(in_file, 0, SEEK_SET);     // Return to the beginning of the file

    if (file_size == 0) {
        printf("Input file is empty.\n");
        fclose(in_file);
        fclose(out_file);
        return;
    }
