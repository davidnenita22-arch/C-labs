# Pawn Shop Registry Management System

This program was developed as **Laboratory Work No. 5** (Part 2) for the **Data Structures and Algorithms** course. It demonstrates an advanced procedural approach to data management in C, focusing on **dynamic memory allocation**, **pointer-based traversal**, and **persistent file I/O**.

---

## 1. Project Purpose
The primary goal is to manage a registry of pledged objects while calculating retention periods and performing data sorting. The program is designed to:
* Dynamically allocate memory for a specific number of pawn records (`malloc`).
* Store raw customer and object data in a working file (`experiment.txt`).
* Calculate the duration an object has been in pawn (Years and Months) relative to the **current system date**.
* Implement a sorting algorithm to organize records in **descending order** based on duration.
* Export analyzed results to `output1.txt` and append them to the primary registry for history tracking.

## 2. Technical Implementation
* **Memory Management**: Uses `malloc()` to allocate a block of memory specifically for the requested number of `PawnRecord` structures, followed by `free()` to prevent memory leaks.
* **Pointer Arithmetic**: Navigates through the dynamic array using pointer offsets `(records + i)` and accesses member fields via the arrow operator (`->`).
* **Advanced Sorting**: Utilizes the standard library `qsort` for high-efficiency $O(N \log N)$ sorting based on total months calculated.
* **Time Integration**: Uses `<time.h>` to fetch the real-world date, ensuring calculations remain accurate regardless of when the program is run.

## 3. Function Overview
The logic is divided into modular functions to ensure code clarity and procedural compliance:

| Function | Description |
| :--- | :--- |
| `inputRecords` | Collects customer and object data from the keyboard using pointers. |
| `saveToExperimentFile` | Writes the initial raw data into `experiment.txt`. |
| `calculateDurations` | Computes the time elapsed since the contract date using system time. |
| `sortRecordsDescending` | Sorts the registry using a custom comparator function for `qsort`. |
| `appendFileToFile` | Merges the analyzed report from `output1.txt` into the end of `experiment.txt`. |
| `testReadMode` | Verifies that all files were correctly closed and are available for reading. |

## 4. Usage
1. **Compile**: Use a standard C compiler (e.g., `gcc Lab5_part2.c -o Lab5_part2`).
2. **Input**: Enter the total number of records you wish to process.
3. **Analyze**: Provide the name, object details, and dates (Contract/Maturity).
4. **Review**: Examine `experiment.txt` for the combined log or `output1.txt` for the sorted duration report.

---

### Author Information
* **Student**: Neniţa David, Group FAF-252.
* **Institution**: Technical University of Moldova, Faculty of Computers, Informatics and Microelectronics.
* **Supervisor**: Burlacu Natalia, PhD.
* **Date**: April 2026.