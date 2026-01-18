# Nature Narrative Grammar Generator | CMPM147 Names Grammar Tiny Generator

## Overview

This generator creates novel inspired landscape descriptions for games and worldbuilding. It combines place types such as mountains or forests with mood-based vocabulary to quickly produce consistent, atmospheric text. Available tones currently include majestic, harsh, generic, and doom. The output features multiple descriptions to both an executable and a file, which can be used as an efficient tool for prototyping environments and generating narrative content.

---

## Files

1. `main.h` - Defines the data structures and function prototypes for a procedural fantasy landscape narrative generator.
2. `main.cpp` - Seeds the random generator, loads the grammar data, and outputs procedurally generated text for four different tones to both the console and a file.
3. `generator.cpp` - Contains the core functions and vocabulary for generating narrative sentences through random selection and template substitution.
4. `names.json` - Provides a vocabulary library and sentence templates for the narrative generator.
5. `makefile` - Builds a C++ program from source files and defines targets for running, cleaning, and testing the narrative generator.
6. `narrative_generator` - File the program builds to.
7. `narrative_output.txt` - Output file.

---

## Usage

Example files `narrative_generator` and `narrative_output.txt` are provided. Otherwise run the following:
1. `make clean`
2. `make`
3. `make run`
---
To view the files:
1. `./narrative_generator` in the terminal after running `make`.
2. Manually open `narrative_output.txt`.

---

## Citation

1. CoPilot used to generate list of descriptors.
2. Thesaurus used to find synonyms for generic nature words.