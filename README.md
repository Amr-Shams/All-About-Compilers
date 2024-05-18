# Compiler Project

## Overview

Welcome to the Compiler Project! This project is designed to support a variety of data types, control structures, type conversions, arithmetic and logical operations, as well as providing comprehensive warnings and errors. The project aims to generate a symbol table, produce code, and highlight any warnings and errors during the compilation process.

![alt text](image.png)

## Features

### Supported Data Types
- **int**: Integer data type
- **float**: Floating-point data type
- **char**: Character data type
- **string**: String data type
- **boolean**: Boolean data type (true/false)
- **void**: Used for functions that do not return a value

### Supported Control Structures
- **func**: Function definitions and calls
- **enum**: Enumeration types
- **while**: While loops
- **do while**: Do-while loops
- **for**: For loops

### Conditional Statements and Type Conversions
- **if**: If statements
- **switch**: Switch-case statements
- **type_conversion**: Implicit and explicit type conversions
- **arithmetic_operations**: +, -, *, /, etc.
- **logical_operations**: &&, ||, !, etc.

### Warnings and Errors
- **Warnings**:
  - Unused variables
  - Conditions that are always true or false
- **Errors**:
  - Double declaration of variables
  - Incompatible type assignments

### Output
- **Symbol Table**: A table of all symbols (variables, functions, etc.) used in the code
- **Code Generation**: The generated code after compilation
- **Warnings**: List of any warnings encountered during compilation
- **Errors**: List of any errors encountered during compilation

## Assumptions
- All control structures (`if`, `for`, `while`, etc.) must use `{}` even if they contain a single line of code.

## Reference Table

| Feature           | Description                                                                 |
|-------------------|-----------------------------------------------------------------------------|
| Data Types        | `int`, `float`, `char`, `string`, `boolean`, `void`                         |
| Control Structures| `func`, `enum`, `while`, `do while`, `for`                                  |
| Conditionals      | `if`, `switch`                                                              |
| Operations        | `type_conversion`, `arithmetic_operations`, `logical_operations`            |
| Warnings          | Unused variables, Conditions always true/false                              |
| Errors            | Double declaration, Incompatible type assignments                           |
| Outputs           | Symbol Table, Code Generation, Warnings, Errors                             |

## Getting Started

To get started with this project, follow the steps below:

### Prerequisites
- Ensure you have a C++ compiler installed on your machine.
- bison and flex should be installed on your machine. version 3.7.6 is recommended.
- npm should be installed on your machine.
- Clone the repository to your local machine.

### Run
- to run the code in the terminal, run the following command:
```sh
git clone https://github.com/your-repo/compiler-project.git
cd Compilers
make
```
- to debug the code, run the following command:
```sh
make debug
```
- to run the GUI, run the following command:
```sh
cd frontend
npm install
npm start
```
- start the server
```sh
cd backend
node server.js
```
- open your browser and go to `http://localhost:3000/`
