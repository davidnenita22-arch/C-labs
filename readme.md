# String Analysis and Sentence Processing

[cite_start]This program was developed as **Laboratory Work No. 3** for the **Data Structures and Algorithms** course[cite: 6, 7]. [cite_start]It demonstrates a procedural approach to string manipulation in C, focusing on **dynamic memory management** and **pointer-based traversal**[cite: 13, 31].

---

## 1. Project Purpose
[cite_start]The primary goal is to analyze a user-provided string to extract specific linguistic metrics while maintaining high memory efficiency[cite: 13, 20]. The program is designed to:
* [cite_start]Create and populate a text file (`input.txt`) with keyboard-entered data[cite: 15, 23].
* [cite_start]Count the total number of **interrogative sentences** (ending with `?`)[cite: 16, 26].
* [cite_start]Determine the character length of the **second interrogative sentence**[cite: 17, 27].
* [cite_start]Identify the **longest sentence** (by character count) in the entire string[cite: 18].
* [cite_start]Export all findings to both the terminal and an `output.txt` file[cite: 19, 29].

## 2. Technical Implementation
* [cite_start]**Memory Management**: Uses `malloc()` to dynamically allocate buffers based on a user-specified maximum length, ensuring no memory is wasted on small inputs[cite: 20, 32, 503].
* [cite_start]**Pointer Arithmetic**: Traversal and analysis are performed entirely via pointers rather than array indexing[cite: 20, 33, 501].
* [cite_start]**Complexity**: The algorithm achieves $O(N)$ complexity by processing the string in a single pass[cite: 501].
* [cite_start]**Robustness**: Includes a "peek-ahead" mechanism to handle compound punctuation like `!?` correctly[cite: 504].

## 3. Function Overview
[cite_start]The logic is divided into modular functions to ensure code clarity[cite: 31, 37]:

| Function | Description |
| :--- | :--- |
| `createAndWriteInputFile` | [cite_start]Handles the creation of `input.txt` and writes the raw input string to it[cite: 43, 172]. |
| `analyzeSentences` | [cite_start]The core logic that calculates counts, lengths, and identifies the longest sentence[cite: 46, 190]. |
| `displayResults` | [cite_start]Formats and outputs the calculated data to the user console[cite: 52, 340]. |
| `writeOutputFile` | [cite_start]Persists the final analysis results into `output.txt`[cite: 54, 370]. |

## 4. Usage
1. [cite_start]**Compile**: Use a standard C compiler (e.g., `gcc lab10.c -o StringFinder`)[cite: 418, 445].
2. [cite_start]**Input**: Provide the maximum expected string length when prompted[cite: 84, 116].
3. [cite_start]**Review**: Check the terminal for immediate results or open `output.txt` for the saved report[cite: 159, 160].

---

### Author Information
* [cite_start]**Student**: Neniţa David, Group FAF-252[cite: 4].
* [cite_start]**Institution**: Technical University of Moldova, Faculty of Computers, Informatics and Microelectronics[cite: 3].
* [cite_start]**Supervisor**: Burlacu Natalia, PhD[cite: 9].
* [cite_start]**Date**: 2026[cite: 11].