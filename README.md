# File Zipper using Huffman Algorithm

This project is a file zipper application that utilizes the Huffman algorithm to compress and decompress files efficiently. The Huffman algorithm is a popular method for lossless data compression, particularly for text files.

## Features

- **Compression**: Allows users to compress a text file (.txt) using the Huffman algorithm. The compressed file is saved with a .bin extension.
- **Decompression**: Enables users to decompress a previously compressed file back to its original format (.txt).
- **Demo Compression**: Provides a demo compression functionality, allowing users to visualize the compression process by generating a compressed file in text format (.txt).

## File Formats

- **Input File**: Files to be compressed should be in the .txt format.
- **Compressed File**: The compressed output file is saved with a .bin extension.
- **Demo Compressed File**: A text representation of the compressed file, stored with a .txt extension.
- **Decompressed File**: The decompressed output file is saved in .txt format.
- **Huffman Tree File**: The generated Huffman tree is saved in a text file (.txt) format.

## Usage

1. **Compile the Code**: Compile the source code file using a C++ compiler.
2. **Run the Executable**: Execute the compiled program.
3. **Choose Operation**:
    - **Compress a File**: Select this option to compress a text file.
    - **Decompress a File**: Choose this option to decompress a previously compressed file.
    - **Demo Compress a File**: Use this option to perform a demo compression and visualize the process.
    - **Exit**: Exit the program.

## Instructions

- When compressing a file, the user is prompted to enter the input and output file names. The output file will be saved with the .bin extension.
- During decompression, the user needs to provide the name of the compressed file (with the .bin extension) and the desired output file name (in .txt format).
- For demo compression, the user specifies the input file name, and the demo compressed file is generated in text format (.txt).
- The Huffman tree generated during compression is kept in a separate file with the name huffmanTree for reference.

## Dependencies

- This project requires a C++ compiler to compile the source code.
- The code utilizes standard C++ libraries and does not require any external dependencies.

## Contributors

- asmanya

## License

This project is licensed under the [MIT License](LICENSE).
