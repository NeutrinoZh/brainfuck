# Brainfuck interpreter

![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)

A simple Brainfuck interpreter written in C++. Brainfuck is a minimal and esoteric programming language with an extremely limited set of commands, making it an excellent subject for study and amusement.

Just for fun. Enjoy! 

## Usage

1. Clone the repository:

    ```bash
    git clone https://github.com/neutrinozh/brainfuck.git
    ```
2. Build the project:

    ```bash
    cd brainfuck
    cmake -B ./build/
    cmake --build ./build/
    ```
3. Run the interpreter with a Brainfuck program:

    ```bash
    cd ..
    ./build/brainfuck ./examples/hello-world.bf
    ```

## Examples

Sample Brainfuck programs can be found in the `examples` directory. You can use them to test the interpreter.

## Brainfuck Syntax

Brainfuck consists of only 8 commands:

- `>`: Increment the pointer
- `<`: Decrement the pointer
- `+`: Increment the value at the current cell
- `-`: Decrement the value at the current cell
- `[`: Begin loop (jump forward to the corresponding `]` if the value at the current cell is 0)
- `]`: End loop (jump back to the corresponding `[` if the value at the current cell is nonzero)
- `,`: Input a character (ASCII)
- `.`: Output a character (ASCII)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.