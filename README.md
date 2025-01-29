# Interpreter

This project is a simple interpreter for a custom programming language. It can read and execute code from a file or run an interactive prompt for executing code line by line.

## Features

- Lexical analysis (tokenization)
- Syntax analysis (parsing)
- Execution of code

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
./interpreter
```

Then enter `1` and provide the path to the file when prompted.

#### Prompt Mode

To run the interactive prompt, use the following command:

```sh
./interpreter
```

Then enter `2` to start the prompt.

## Usage

### Example Code

Here is an example of the custom language syntax:

```
var x = 10;
print(x + 2);
```

### Running the Example

Save the example code to a file (e.g., `example.lox`) and run the interpreter in file mode, providing the path to the file.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

## License

This project is licensed under the MIT License.