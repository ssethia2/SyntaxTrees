# CS 126 FinalProject - Syntax Trees

This application accepts parts-of-speech tags of English, and constructs the Syntax Trees based on [**X-Bar Theory**](https://en.wikipedia.org/wiki/X-bar_theory). It uses [**openFrameWorks**](http://openframeworks.cc/) v9.8 to draw the visualization of the trees.

The project is written in C++ in Visual Studio 15 (2017 Community) edition.

To use this project or extend it: 

+ Clone or download the git repository
+ Open the syntax_trees.sln file using Visual Studio
+ Build using the Win32 option
+ Run the Local Windows Debugger

Once the openFrameworks window opens, type in the parts-of-speech tags of a sentence under the prompt to construct its tree.
Acceptable tags with a space in between are:

+ D - Determiner
+ N - Noun
+ Adj - Adjective
+ Adv - Adverb
+ V - Verb
+ P - Preposition

Example of use:
Sentence - The man kicked the ball
Tags -      D   N    V     D    N

-------

Unit tests were written for testing proper tree construction using [*Catch*](https://github.com/catchorg/Catch2) and compiled using [*CMake*](https://cmake.org/). A CMakeLists.txt file is provided for unit tests. 

To run the unit tests:

+ Open the test folder in folder view in Visual Studio
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
