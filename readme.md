# String Analysis and Sentence Processing

This program was developed as **Laboratory Work No. 3** for the **Data Structures and Algorithms**. It demonstrates a procedural approach to string manipulation in C, focusing on **dynamic memory management** and **pointer-based traversal**.

---

## 1. Project Purpose
The primary goal is to analyze a user-provided string to extract specific linguistic metrics while maintaining high memory efficiency. The program is designed to:
* Create and populate a text file (`input.txt`) with keyboard-entered data.
* Count the total number of **interrogative sentences** (ending with `?`).
* Determine the character length of the **second interrogative sentence**.
* Identify the **longest sentence** (by character count) in the entire string.
* Export all findings to both the terminal and an `output.txt` file.

## 2. Technical Implementation
* **Memory Management**: Uses `malloc()` to dynamically allocate buffers based on a user-specified maximum length, ensuring no memory is wasted on small inputs.
* **Pointer Arithmetic**: Traversal and analysis are performed entirely via pointers rather than array indexing.
* **Complexity**: The algorithm achieves $O(N)$ complexity by processing the string in a single pass.
* **Robustness**: Includes a "peek-ahead" mechanism to handle compound punctuation like `!?` correctly.

## 3. Function Overview
The logic is divided into modular functions to ensure code clarity:

| Function | Description |
| :--- | :--- |
| `createAndWriteInputFile` | Handles the creation of `input.txt` and writes the raw input string to it. |
| `analyzeSentences` | The core logic that calculates counts, lengths, and identifies the longest sentence. |
| `displayResults` | Formats and outputs the calculated data to the user console. |
| `writeOutputFile` | Persists the final analysis results into `output.txt`[. |

## 4. Usage
1. **Compile**: Use a standard C compiler (e.g., `gcc lab10.c -o StringFinder`).
2. **Input**: Provide the maximum expected string length when prompted.
3. **Review**: Check the terminal for immediate results or open `output.txt` for the saved report.

---

### Author Information
* **Student**: Neniţa David, Group FAF-252.
* **Institution**: Technical University of Moldova, Faculty of Computers, Informatics and Microelectronics.
* **Supervisor**: Burlacu Natalia, PhD.
* **Date**: 2026.