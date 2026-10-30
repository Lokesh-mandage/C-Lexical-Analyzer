# C Lexical Analyzer

## Overview
A Lexical Analyzer developed using C programming language. It reads a C source file and identifies different tokens.

## Features
- Keyword identification
- Identifier identification
- Constant identification
- Operator identification
- Special symbol identification
- String and character identification
- Single-line and multi-line comment identification
- Preprocessor directive identification
- Invalid token detection

## Technologies Used
- C Programming
- GCC Compiler
- VS Code

## Project Structure
- main.c – Main program
- lexer.c – Token identification functions
- lexer.h – Function declarations
- types.h – Token type definitions
- sample.c – Sample input program

## How to Compile and Run

```bash
gcc main.c lexer.c -o lexer
./lexer sample.c