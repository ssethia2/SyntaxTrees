# CS 126 FinalProject - Syntax Trees

This project uses [**openFrameWorks**](http://openframeworks.cc/) to accept parts of speech of English, and constructs the Syntax Trees based on [**X-Bar Theory**](https://en.wikipedia.org/wiki/X-bar_theory).

The project is written in C++ in Visual Studio 15 (2017 Community) edition.

To use this project or extend it: 

+ Clone or download the git repository
+ Open the syntax_trees.sln file using Visual Studio
+ Build using the Win32 option
+ Run the Local Windows Debugger

Unit tests were written for testing proper tree construction using [*Catch*](https://github.com/catchorg/Catch2) and compiled using [*CMake*](https://cmake.org/). A CMakeLists.txt file is provided for unit tests. 

To run the unit tests:

+ Open the test folder in solution view in Visual Studio
+ Generate the CMake cache
+ Build only the test.exe executable using the CMake tab in Visual Studio

Other platforms *may* or *may not* be suited to run the application or unit tests.

Author(s):

+ **Satvik Sethia**

Acknowledgements:

+ Professor Graham Carl Evans
+ Arnav Sankaran
+ Dachun Sun
+ Dillon Hammond
+ Nicolas Nytko
+ Will Koster
+ Yash Sharma
+ Ethan Cheng
