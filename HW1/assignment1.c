#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *file_path = "sample.txt";

    // Open the file in read-write mode
    int file_descriptor = open(file_path, O_RDWR);

    if (file_descriptor == -1) {
        perror("Failed to open the file");
        return 1;
    }

    // Use lseek and read to print "student."
    off_t read_offset = 14; // Offset to start of "student."
    lseek(file_descriptor, read_offset, SEEK_SET);

    char buffer[8];  // "student." has 8 characters
    int read_bytes = read(file_descriptor, buffer, sizeof(buffer));

    if (read_bytes == -1) {
        perror("Error reading from file");
        close(file_descriptor);
        return 1;
    }

    buffer[read_bytes] = '\0'; // Null-terminate the string
    write(STDOUT_FILENO, buffer, read_bytes);
    write(STDOUT_FILENO, "\n", 2); // New line

    // Use lseek and write to replace "student." with "NTHU student."
    off_t write_offset = 14; // Offset to start of "student."
    lseek(file_descriptor, write_offset, SEEK_SET);

    const char *replacement = "NTHU student.";
    int write_bytes = write(file_descriptor, replacement, strlen(replacement));

    if (write_bytes == -1) {
        perror("Error writing to file");
        close(file_descriptor);
        return 1;
    }

    // Print the whole sentence in the file
    // Reset file offset to the beginning
    lseek(file_descriptor, 0, SEEK_SET);

    // Read and print the whole sentence
    char whole_sentence[100];
    int read_whole_bytes = read(file_descriptor, whole_sentence, sizeof(whole_sentence));

    if (read_whole_bytes == -1) {
        perror("Error reading from file");
        close(file_descriptor);
        return 1;
    }

    whole_sentence[read_whole_bytes] = '\0'; // Null-terminate the string
    write(STDOUT_FILENO, whole_sentence, read_whole_bytes);
    // Close the file
    close(file_descriptor);

    return 0;
}
