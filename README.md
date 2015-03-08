# LispInt
# Sreyas Srimath Tirumala (srimath-tirumala.1)

This folder contains the following files:

lispInt - This is the main file which handles console i/o and starts off everythin.

expression (.cpp and .h) - This class contains information about the binary tree structure in which the s-expressions are stored.

parser (.cpp .h) - This class contains the parser which first prunes the string, then recursively parses it to generate a binary tree. This binary tree is then traversed to get the final dot notation.

definitions - This class is supposed to contain all the external headers and any internal common structures. This is very barebones right now but it is sensible to keep such a header to include all external dependencies.

HOW TO RUN:

Simple:
1) make
2) ./lispInt
