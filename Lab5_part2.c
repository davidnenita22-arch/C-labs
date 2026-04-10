#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char name[50];
    char surname[50];
    char objectName[100];
    double value;
    Date contractDate;
    Date maturityDate;
    
    // Calculated fields
    int durationYears;
    int durationMonths;
    int totalDurationInMonths; 
} PawnRecord;

void clearInputBuffer();
void inputRecords(PawnRecord* records, int count);
void saveToExperimentFile(PawnRecord* records, int count, const char* filename);
void displayFromFile(const char* filename);
void calculateDurations(PawnRecord* records, int count);
void sortRecordsDescending(PawnRecord* records, int count);
void saveToOutputFile(PawnRecord* records, int count, const char* filename);
void appendFileToFile(const char* sourceFilename, const char* destFilename);
void testReadMode(const char* filename1, const char* filename2);

// Main Program 
int main() {
    int recordCount;
    const char* expFile = "experiment.txt";
    const char* outFile = "output1.txt";

    printf("\nPawn Shop Registry System \n");
    printf("Enter the number of records you want to input: ");
    if (scanf("%d", &recordCount) != 1 || recordCount <= 0) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }
    clearInputBuffer();

    // Dynamically allocate memory for the records using pointers
    PawnRecord* registry = (PawnRecord*)malloc(recordCount * sizeof(PawnRecord));
    if (registry == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input data and store in experiment.txt
    inputRecords(registry, recordCount);
    saveToExperimentFile(registry, recordCount, expFile);

    // Display the data recently entered in the given file
    printf("\n Data successfully written. Reading from %s \n", expFile);
    displayFromFile(expFile);

    // Calculate duration of the object being in pawn
    calculateDurations(registry, recordCount);

    // Sort and enter results into output.txt
    sortRecordsDescending(registry, recordCount);
    saveToOutputFile(registry, recordCount, outFile);
    printf("\n Calculated durations sorted descending and saved to %s \n", outFile);

    // Copy entire data from output.txt to the end of experiment.txt
    appendFileToFile(outFile, expFile);
    printf("Data from %s successfully appended to %s \n", outFile, expFile);

    // Test opening both files in read mode
    testReadMode(expFile, outFile);

    // Free allocated memory
    free(registry);
    printf("\nProgram executed successfully. Memory freed.\n");

    return 0;
}

// Function Implementations 

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inputRecords(PawnRecord* records, int count) {
    for (int i = 0; i < count; i++) {
        PawnRecord* current = (records + i); // Pointer arithmetic
        printf("\n Entering details for Record #%d \n", i + 1);
        
        printf("Customer Name: ");
        scanf("%49s", current->name);
        
        printf("Customer Surname: ");
        scanf("%49s", current->surname);
        clearInputBuffer();
        
        printf("Pledged Object Name: ");
        fgets(current->objectName, 100, stdin);
        current->objectName[strcspn(current->objectName, "\n")] = 0; // Remove trailing newline
        
        printf("Pledged Object Value (MDL): ");
        scanf("%lf", &current->value);
        
        printf("Contract Date (DD MM YYYY): ");
        scanf("%d %d %d", &current->contractDate.day, &current->contractDate.month, &current->contractDate.year);
        
        printf("Maturity Date (DD MM YYYY): ");
        scanf("%d %d %d", &current->maturityDate.day, &current->maturityDate.month, &current->maturityDate.year);
        clearInputBuffer();
    }
}

void saveToExperimentFile(PawnRecord* records, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file %s\n", filename);
        return;
    }

    fprintf(file, " RAW PAWN SHOP REGISTRY \n");
    for (int i = 0; i < count; i++) {
        PawnRecord* r = (records + i);
        fprintf(file, "Customer: %s %s | Object: %s | Value: %.2f MDL | Contract: %02d/%02d/%04d | Maturity: %02d/%02d/%04d\n",
                r->name, r->surname, r->objectName, r->value, 
                r->contractDate.day, r->contractDate.month, r->contractDate.year,
                r->maturityDate.day, r->maturityDate.month, r->maturityDate.year);
    }
    fclose(file);
}

void displayFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading.\n", filename);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void calculateDurations(PawnRecord* records, int count) {
    // Get current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;

    for (int i = 0; i < count; i++) {
        PawnRecord* r = (records + i);
        
        // Calculate total months difference
        int monthsPassed = (currentYear - r->contractDate.year) * 12 + (currentMonth - r->contractDate.month);
        
        if (monthsPassed < 0) {
            monthsPassed = 0; // Prevent negative durations if contract is somehow in the future
        }

        r->totalDurationInMonths = monthsPassed;
        r->durationYears = monthsPassed / 12;
        r->durationMonths = monthsPassed % 12;
    }
}

// Comparator function for qsort (Descending order based on totalDurationInMonths)
int compareDurations(const void* a, const void* b) {
    PawnRecord* recordA = (PawnRecord*)a;
    PawnRecord* recordB = (PawnRecord*)b;
    return (recordB->totalDurationInMonths - recordA->totalDurationInMonths);
}

void sortRecordsDescending(PawnRecord* records, int count) {
    qsort(records, count, sizeof(PawnRecord), compareDurations);
}

void saveToOutputFile(PawnRecord* records, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file %s\n", filename);
        return;
    }

    fprintf(file, " DURATION RESULTS (SORTED DESCENDING) \n");
    for (int i = 0; i < count; i++) {
        PawnRecord* r = (records + i);
        fprintf(file, "Object: %s | Client: %s %s | Time in Pawn: %d Years and %d Months\n",
                r->objectName, r->name, r->surname, r->durationYears, r->durationMonths);
    }
    fclose(file);
}

void appendFileToFile(const char* sourceFilename, const char* destFilename) {
    FILE* srcFile = fopen(sourceFilename, "r");
    FILE* destFile = fopen(destFilename, "a"); // 'a' mode appends to the end of the file

    if (srcFile == NULL || destFile == NULL) {
        printf("Error opening files for appending operation.\n");
        if (srcFile) fclose(srcFile);
        if (destFile) fclose(destFile);
        return;
    }

    fprintf(destFile, "\n APPENDED FROM %s \n", sourceFilename);
    char ch;
    while ((ch = fgetc(srcFile)) != EOF) {
        fputc(ch, destFile);
    }

    fclose(srcFile);
    fclose(destFile);
}

void testReadMode(const char* filename1, const char* filename2) {
    printf("\n Testing Read Modes \n");
    FILE* f1 = fopen(filename1, "r");
    FILE* f2 = fopen(filename2, "r");

    if (f1 != NULL) {
        printf("[OK] %s can be opened in read mode.\n", filename1);
        fclose(f1);
    } else {
        printf("[FAIL] Could not open %s in read mode.\n", filename1);
    }

    if (f2 != NULL) {
        printf("[OK] %s can be opened in read mode.\n", filename2);
        fclose(f2);
    } else {
        printf("[FAIL] Could not open %s in read mode.\n", filename2);
    }
}