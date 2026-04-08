#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void createAndWriteInputFile(const char *filename, const char *str);
void analyzeSentences(const char *str, int *qCount, int *secondLen);
void displayResults(int qCount, int secondLen);
void writeOutputFile(const char *filename, int qCount, int secondLen);

int main() {
    int length;
    
    // 1. Get length and dynamically allocate memory (Requirement B from Image 2)
    printf("Enter the maximum length of your input string: ");
    if (scanf("%d", &length) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    // Clear the input buffer before reading the string
    while (getchar() != '\n');

    // Allocate memory using malloc
    char *inputString = (char *)malloc((length + 1) * sizeof(char));
    if (inputString == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // 2. Allow input of a string from the keyboard
    printf("Enter the string: ");
    fgets(inputString, length + 1, stdin);
    
    // Strip the trailing newline character left by fgets
    inputString[strcspn(inputString, "\n")] = '\0';

    // 3. Create input.txt and store the string
    createAndWriteInputFile("input.txt", inputString);

    // Variables to hold our target data
    int interrogativeCount = 0;
    int secondSentenceLength = 0;

    // 4. Call our functions to process data using pointers
    analyzeSentences(inputString, &interrogativeCount, &secondSentenceLength);
    
    // 5. Display results to screen
    displayResults(interrogativeCount, secondSentenceLength);

    // 6. Write results to output.txt
    writeOutputFile("output.txt", interrogativeCount, secondSentenceLength);

    // Free dynamically allocated memory
    free(inputString);
    printf("\n[Process completed. Check input.txt and output.txt]\n");

    return 0;
}


/* Creates 'input.txt' and writes the keyboard-entered string to it */
void createAndWriteInputFile(const char *filename, const char *str) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating input file");
        exit(EXIT_FAILURE);
    }
    fputs(str, file);
    fclose(file);
}

/* * Analyzes the string using pointer arithmetic (Requirement A).
 * Identifies interrogative sentences and calculates the length of the 2nd one.
 * Time Complexity: O(N) single-pass traversal.
 */
void analyzeSentences(const char *str, int *qCount, int *secondLen) {
    *qCount = 0;
    *secondLen = 0;
    
    int currentLen = 0;
    const char *ptr = str; // Pointer to traverse the string

    while (*ptr != '\0') {
        // Skip leading whitespace for accurate sentence length calculation
        if (currentLen == 0 && isspace(*ptr)) {
            ptr++;
            continue;
        }

        currentLen++;

        if (*ptr == '?') {
            // Found an interrogative sentence
            (*qCount)++;
            if (*qCount == 2) {
                *secondLen = currentLen; // Store length of the 2nd one
            }
            currentLen = 0; // Reset length counter for the next sentence
        } 
        else if (*ptr == '.' || *ptr == '!') {
            // Found a regular or exclamatory sentence, just reset length
            currentLen = 0;
        }
        ptr++;
    }
}

/* Displays the extracted data to the screen */
void displayResults(int qCount, int secondLen) {
    printf("\n--- Output Information ---\n");
    printf("Number of interrogative sentences found: %d\n", qCount);
    
    if (qCount >= 2) {
        printf("Length of the second interrogative sentence: %d characters\n", secondLen);
    } else {
        printf("Length of the second interrogative sentence: N/A (Less than 2 found)\n");
    }
}

/* Writes the identical displayed data to output.txt */
void writeOutputFile(const char *filename, int qCount, int secondLen) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating output file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "Number of interrogative sentences found: %d\n", qCount);
    if (qCount >= 2) {
        fprintf(file, "Length of the second interrogative sentence: %d characters\n", secondLen);
    } else {
        fprintf(file, "Length of the second interrogative sentence: N/A (Less than 2 found)\n");
    }
    
    fclose(file);
}