To clone this project, run the command:

		git clone https://github.com/maavumich/project0

...in a terminal. This will create a directory in the present working
directory ("`PWD`") called `project0` that contains all of the files in
this repository.

# Training Project 0

The basics of C++. Basic syntax, header files, Makefiles, Linux terminal
commands. The optional zeroth project in the core training sequence.

Trainees will write functions that solve "basic coding knowledge interview
questions", as well as the additional "infrastructure" needed to compile
that code. Trainees will also learn how to Linux.

The goal of Training Project 0 is to bring trainees up to speed with the
particulars of C++ syntax and the quirks of coding in the language.

Instructions and pass requirements are found in the `./docs` folder inside
`./docs/assignment.md`.

## Topics Covered

If this list looks imposing, don't let it frighten you. The author of this
project likes tryharding and big words.

* How to terminal
	* File-system navigation
	* File manipulation (creating and removing folders; creating, renaming,
	  and moving files)
	* The `rm` command
	* Basic regular expressions (or, "why `rm -rf ~/*` will make you deeply sad)
	* `stdout`, `stderr`, and file redirection
* Basic SSH usage
	* The university's CAEN servers
	* Command-line text editors
	* Copying files with `scp`
	* SSH aliases
* C++ syntax
	* Meaningful-versus-non-meaningful whitespace
	* Semicolons
	* Variables and variable scopes
	* Conditional statements (if-then)
	* Loops (while, for, range-for)
	* Switch cases
	* Function headers and forward declaration
* Coding style
	* Indentation (tabs vs. spaces vs. tabs-with-spaces-for-alignment)
	* Where to put curly braces (Kernighan and Ritchie vs. Allman)
* The compilation process / What `#include` actually does
* Main functions
* Classes
	* The `new` keyword and how it might not do what you expect
	* Constructors and constructing objects
	* Access specifiers (`public`, `private`)

## Directory Structure

### Documentation 			[`./docs`]

The project spec, as well as informational resources on the topics covered
by this project.

Contains:
* The assignment, in detail (`./docs/assignment.md`)
* How to self-grade your project (`./docs/grading.md`)
* Links to other helpful resources (`./docs/notes.md`).

### Source					[`./src`]

The actual project implementation.

Contains:
* Starter files
	* `./src/AClass.cpp`
	* `./src/AStruct.cpp`
	* `./src/Makefile`
	* `./src/project0.cpp`

### Potentially Useful		[`./maybe_useful`]

Some resources that you might find useful while working on your project.
Non-essential to the project itself.
