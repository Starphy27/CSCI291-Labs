#include <stdio.h>      // Include standard input/output functions
#include <stdlib.h>     // Include standard library functions for memory allocation and process control
#include <ctype.h>      // Include functions for character classification (e.g., isdigit, isspace)
#include <string.h>     // Include string manipulation functions (e.g., strcpy, strncpy)
#include <errno.h>      // Include functions for error handling and strerror

#define MAX_LINE_LENGTH 1024  // Define maximum line length for reading from file
#define MAX_TOKEN_LENGTH 100  // Define maximum token length
#define INPUT_FILENAME "data.txt"  // Define the input file name
#define OUTPUT_FILENAME "valid_floats.txt"  // Define the output file name

// Verbose error logging macro to log errors with file name, line number, and error message
#define LOG_ERROR(msg) fprintf(stderr, "ERROR [%s:%d]: %s - %s\n", __FILE__, __LINE__, msg, strerror(errno))

// Function to check if a string represents a valid float
int is_valid_float(const char* str) {
    int dot_count = 0;  // Count of dots in the string
    int digit_count = 0;  // Count of digits in the string
    int sign_count = 0;  // Count of signs ('+' or '-') in the string

    // Skip leading whitespace characters
    while (isspace(*str)) {
        str++;
    }

    // Check for an optional sign (+ or -)
    if (*str == '+' || *str == '-') {
        sign_count++;  // Increment sign count
        str++;  // Move to next character
    }

    // Process each character in the string
    while (*str != '\0' && !isspace(*str)) {
        if (*str == '.') {
            dot_count++;  // Increment dot count if a dot is found
            // Only one dot is allowed
            if (dot_count > 1) {
                return 0;  // Invalid float if more than one dot
            }
        } 
        else if (!isdigit(*str)) {
            // Invalid character found (not a digit or dot)
            return 0;
        }
        else {
            digit_count++;  // Increment digit count if a digit is found
        }
        str++;  // Move to next character
    }

    // Return true if there is at least one digit and no more than one dot
    return (digit_count > 0 && dot_count <= 1);
}

// Function to process file using fseek
int process_file_with_fseek(const char* input_filename, const char* output_filename) {
    FILE *input_file = NULL, *output_file = NULL;  // File pointers for input and output files
    char buffer[MAX_LINE_LENGTH];  // Buffer to hold file content temporarily
    char token[MAX_TOKEN_LENGTH];  // Token for holding a single token from the file
    long file_size = 0;  // File size in bytes
    size_t bytes_read = 0;  // Number of bytes read from the input file
    int invalid_count = 0;  // Count of invalid floats
    int valid_count = 0;  // Count of valid floats
    char *current_pos, *buffer_end;  // Pointers for navigating through buffer

    // Verify input filename is provided
    if (input_filename == NULL) {
        LOG_ERROR("Invalid input filename");
        return -1;  // Return failure if input filename is null
    }

    // Open input file in read mode
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {  // If file cannot be opened
        LOG_ERROR("Failed to open input file");
        return -1;  // Return failure
    }

    // Determine the size of the file using fseek
    if (fseek(input_file, 0, SEEK_END) != 0) {
        LOG_ERROR("Error seeking to end of file");
        fclose(input_file);
        return -1;  // Return failure if seeking fails
    }

    // Get the current file pointer position, which corresponds to the file size
    file_size = ftell(input_file);
    if (file_size == -1) {  // If there is an error getting the file size
        LOG_ERROR("Error getting file size");
        fclose(input_file);
        return -1;  // Return failure
    }

    // Check if the file is empty
    if (file_size == 0) {
        fprintf(stderr, "WARNING: Input file is empty\n");
        fclose(input_file);
        return 0;  // Return success with warning if the file is empty
    }

    // Reset the file position to the beginning
    if (fseek(input_file, 0, SEEK_SET) != 0) {
        LOG_ERROR("Error resetting file position");
        fclose(input_file);
        return -1;  // Return failure if resetting the file position fails
    }

    // Open output file in write mode
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {  // If output file cannot be created
        LOG_ERROR("Failed to create output file");
        fclose(input_file);
        return -1;  // Return failure
    }

    // Read the entire contents of the input file into the buffer
    bytes_read = fread(buffer, 1, sizeof(buffer) - 1, input_file);
    if (bytes_read == 0) {  // If file reading fails
        LOG_ERROR("Failed to read file contents");
        fclose(input_file);
        fclose(output_file);
        return -1;  // Return failure
    }

    // Null-terminate the buffer to treat it as a string
    buffer[bytes_read] = '\0';
    buffer_end = buffer + bytes_read;

    // Process tokens (words or numbers) in the buffer
    current_pos = buffer;
    while (current_pos < buffer_end) {
        // Skip leading whitespace characters
        while (current_pos < buffer_end && isspace(*current_pos)) {
            current_pos++;
        }

        // Extract a token (sequence of non-whitespace characters)
        char *token_end = current_pos;
        while (token_end < buffer_end && !isspace(*token_end)) {
            token_end++;
        }

        // Copy the token into the token buffer
        size_t token_length = token_end - current_pos;
        if (token_length > 0 && token_length < sizeof(token)) {  // If the token is non-empty and fits in the buffer
            strncpy(token, current_pos, token_length);
            token[token_length] = '\0';  // Null-terminate the token string

            // Validate if the token represents a valid float
            if (is_valid_float(token)) {
                fprintf(output_file, "%s\n", token);  // Write valid token to output file
                valid_count++;  // Increment valid float count
            } else {
                invalid_count++;  // Increment invalid float count
            }
        }

        // Move to the next token in the buffer
        current_pos = token_end;
    }

    // Close the input and output files
    fclose(input_file);
    fclose(output_file);

    // Display the results after processing
    printf("File processing complete:\n");
    printf("File size: %ld bytes\n", file_size);
    printf("Number of valid floats: %d\n", valid_count);
    printf("Number of invalid floats: %d\n", invalid_count);

    return 0;  // Return success
}

int main() {
    // Call the function to process the file
    int result = process_file_with_fseek(INPUT_FILENAME, OUTPUT_FILENAME);

    // Check the result of the file processing
    if (result != 0) {
        fprintf(stderr, "File processing failed. Check error messages above.\n");
        return EXIT_FAILURE;  // Exit with failure status if processing failed
    }

    return EXIT_SUCCESS;  // Exit with success status if processing succeeded
}