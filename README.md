# Interpreter

This project is a simple interpreter for a custom programming language. It can read and execute code from a file or run an interactive prompt for executing code line by line.

## Features

- Lexical Analyzer (Lexer) ✅
  - Lexemes
  - Tokens
- Syntactical Analysis (Parser) ✅
  - Abstract Syntax Tree
  - Recursive Descent Parser
- Execution of Code ️✅

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- CMake (optional, for building the project)

### Building the Project

To build the project, you can use the following commands:

```sh
mkdir build
cd build
cmake ..
make
```

### Running the Interpreter

You can run the interpreter in two modes: file mode and prompt mode.

#### File Mode

To run a file, use the following command:

```sh
./src/Interpreter
```

And provide the path to the file when prompted.

## Usage

### Example Code

Here is an example of the custom language syntax:

```
SUGOD
    MUGNA NUMERO x, y, z = 5
    MUGNA LETRA a_1 = 'n'
    MUGNA TINUOD t = "OO"
    x=y=4
    a_1='c'
    --this is a comment
    IPAKITA: x & t & z & $ & a_1 & [#] & "last"
KATAPUSAN
```

### Running the Example

Save the example code to a file (e.g., `example.txt`) and run the interpreter in file mode, providing the path to the file.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

## License

This project is licensed under the MIT License.
