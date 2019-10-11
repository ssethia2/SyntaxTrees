# Syntax Trees

This application accepts a sentence in English, and constructs the Syntax Trees based on [**X-Bar Theory**](https://en.wikipedia.org/wiki/X-bar_theory).

The project was originally written in C++ in Visual Studio as a stand-alone application. It was rewritten in Python as a web application.

-------

## Linguistics

The tags used for the purposes of this project are:

+ D - Determiner
+ N - Noun
+ Adj - Adjective
+ Adv - Adverb
+ V - Verb
+ P - Preposition

The NLTK library is used to tag the words of the sentences, and the tags are converted to the above forms.

-------

## Testing

Unit tests were written for testing proper tree construction using [*Catch*](https://github.com/catchorg/Catch2) and compiled using [*CMake*](https://cmake.org/). Tests will be rewritten in pytest.

-------

Author(s):

+ **Satvik Sethia**
