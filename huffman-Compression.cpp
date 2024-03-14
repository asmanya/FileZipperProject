// ************************ FILE ZIPPER ****************************

// File Formats : inputFile            -   .txt (INPUT)
//                compressedFile       -   .bin (OUTPUT)
//                demoCompressedFile   -   .txt (OUTPUT)
//                decompressedFile     -   .txt (OUTPUT)
//                huffmanTree          -   .txt (OUTPUT)



#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <direct.h>
#include <bitset>
#include <sys/stat.h>
using namespace std;


// Defining constants

const char NEW_LINE = '$';
const char SPACE = '^';
const char FILE_SPLITTER = '#';


// The struct consists of a character, its freq and two node pointers - this node structure is utilized
// to generate the Huffman Tree structure.

struct Node {

        char ch;
        int freq;
        Node *left, *right;

};


// this comp is used as comprator in priority queue to sort the nodes in required manner.

struct comp {

        // this sorts based on freq on two nodes

        bool operator()(Node *l, Node *r) {
                return l->freq > r->freq;
        }

};


// This function generates the node

Node *getNode(char ch, int freq, Node *left, Node *right) {
        
        Node *node = new Node();
        node->ch = ch;
        node->freq = freq;
        node->left = left;
        node->right = right;
        
        return node;

}


// encode function utilizes the Huffman Tree to generate codes for characters based on the condition
// that for reaching an character from the root node, if the next node chosen is left, '0' is added to
// the Huffman code, else if next node is right, '1' is added to the Huffman code of that character.

void encode(Node *root, string str, unordered_map<char, string> &huffmanTree) {
        if (root == nullptr)
                return;

        // when the node whose left and right pointers are null is reached, i.e. the node that contains the original character
        // the character and its Huffman Code is added to the unordered_map that stores these.        

        if (!root->left && !root->right)
                huffmanTree[root->ch] = str;
        
        // recursive traversal is performed to get to each and every character present in the Huffman Tree.

        encode(root->left, str + "0", huffmanTree);
        encode(root->right, str + "1", huffmanTree);
            
}


// This function is used for creation of Huffman Tree for an input file
// Based on HUFFMAN ALGORITHM

unordered_map<char, string> buildHuffmanTree(unordered_map<char, int> freq, Node *&return_root) {
        
        // Using min head to get the characters with min frequency

        priority_queue<Node *, vector<Node *>, comp> pq;

        // Pushing Nodes into the priority queue

        for (auto pair: freq)
        {
                pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
        }

        // Generating the HUffman Tree by attaching left and right node pointers with parent

        while (pq.size() != 1)
        {
                Node *left = pq.top();
                pq.pop();
                Node *right = pq.top();
                pq.pop();

                int sum = left->freq + right->freq;
                pq.push(getNode('\0', sum, left, right));
        }

        // The remaining element in the priority queue will be the root Node of the Huffman Tree

        Node *root = pq.top();

        // Encoding of charcters if now performed using the Huffman Tree

        unordered_map<char, string> huffmanTree;
        encode(root, "", huffmanTree);

        return_root = pq.top();

        // an unordered_map of every character with its generated Huffman code is returned

        return huffmanTree;

}


// This function uses charMap and ecoded string to create the decode string

string decodeFromCharMap (string &encoded, unordered_map<string, char> &charMap) {

        string cur;
        string decoded = "";
        int ct = 0, totalCount = INT_MAX;

        // checks if "cur" string formed matches with any Huffman code  present in the charMap
        // if it matches the conditions, add the character to decoded string.

        for( int i = 0; i < encoded.size() && ct < totalCount; i++) {
                cur += encoded[i];

                if (charMap.count(cur) > 0) {
                        if(charMap[cur] == NEW_LINE) 
                                decoded += '\n';
                        else if (charMap[cur] == SPACE) 
                                decoded += ' ';
                        else    
                                decoded += charMap[cur];
                        
                        cur = "";
                        ct++;
                }
        }

        // decoded string is returned.

        return decoded;

}


// This function creates a txt file of compressed file

void demoCompressFile(const string &inputFileName, const string &outputFileName) {

        // Used ifstream class to read the input file

        ifstream inFile(inputFileName);
        string line, text;

        // Reading through line by line and storing the data in a string text

        while (getline(inFile, line))
        {
                text += line;
                text += "\n";
        }
        text.resize(text.size() - 1);

        // Creating the root Node for Huffman Tree

        Node *root = nullptr;

        // Counting freq of every character in input file

        unordered_map<char, int> freq;
        for(char ch: text) 
                freq[ch]++;

        // Here the huffman tree for the given input file is generated based on freq of characters.

        unordered_map<char, string> huffmanTree = buildHuffmanTree(freq, root);

        // Using ofstream class to write into "outputFileName" file - this is going to be txt file

        ofstream outFile(outputFileName);
        outFile << "There are " << freq.size() << " unique characters" << "\n";

        string str = "";
        str += "Huffman tree are:\n";

        // creating "str" string with huffmanTree 

        for(char ch : text) 
                str += huffmanTree[ch];

        str += "\nHuffman Codes are: \n";

        // Writing huffman Tree in file

        for( auto pair: huffmanTree)
        {
                if(pair.first == ' ') 
                        str += SPACE;
                else if(pair.first == '\n')
                        str += NEW_LINE;
                else 
                        str += pair.first;

                str += " ";
                str += pair.second;
                str += " ";
                str += to_string(freq[pair.first]);
                str += '\n';
        }

        //writing str string into outFile obk=ject i.e. outputFileName file

        outFile << str;
        outFile.close();

}


// This function is used to compress the file, it takes two paramter strings - which are names of input and output files.

void compressFile(const string& inputFileName, const string &outputFileName) {

        // Used ifstream class to read the input file

        ifstream inFile(inputFileName);
        string line, text;

        // Reading through line by line and storing the data in a string text

        while(getline(inFile, line))
        {
            text += line;
            text += '\n';
        }
        text.resize(text.size() - 1);

        // Creating the root Node for Huffman Tree

        Node* root = nullptr;

        // Counting freq of every character in input file

        unordered_map<char, int> freq;
        int totalCount = 0;
        for(char ch: text)
        {
                freq[ch]++;
                totalCount++;
        }

        // Here the huffman tree for the given input file is generated based on freq of characters.

        unordered_map<char, string> huffmanTree = buildHuffmanTree(freq, root); 

        string binaryFilePath = outputFileName + ".bin";

        // Writing output file using ofstream class, using flag (ios::binary) as its going to be in binary format

        ofstream binaryFile(binaryFilePath, ios:: binary);
        if (!binaryFile)
        {
                cerr << "Binary File is not opening for writing!" << endl;
                return;
        }

        // Writing Huffman tree into compressed output file

        string tree = "";
        int cnt = 1;
        for (auto pair : huffmanTree)
        {
                if (pair.first == ' ')
                        tree += SPACE;
                else if (pair.first == '\n')
                        tree += NEW_LINE;
                else 
                        tree += pair.first;

                tree += " ";
                tree += pair.second;
                tree += "\n";
                cnt++;
        }

        tree.resize(tree.size() - 1);
        string totalCountString = to_string(totalCount);

        // Adding a file splitter between Huffman Tree and the binary code (useful while decoding)

        tree += FILE_SPLITTER;

        binaryFile.write(tree.c_str(), tree.size());

        // Based on Huffman Tree, encoding of characters is done into a string.

        string encoded = "";
        for(char ch: text)
        {
                encoded += huffmanTree[ch];
        }

        int extra = encoded.size() % 8;
        for(int i = 0; i < (8 - extra); i++)
        {
                encoded += "0";
        }

        // Writing the encoded string into binary

        long long int len = encoded.length();
        for(int i = 0; i < len; i+= 8)
        {
                string byteString = encoded.substr(i, 8);
                char byte = (char)(stoi(byteString, nullptr, 2));

                binaryFile.write(&byte, 1);
        }

        binaryFile.close();

        // Mathematics - calculating the size of input and output files
        // Showing the user increase or decrease in the size using diff colors in console

        long long int totalChar = (totalCountString.size() + tree.size() + cnt);
        long long int totalSize = len + (totalChar * 8);
        long long int totalInputSize = (totalCount * 8);

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if ((totalInputSize - totalSize) > 0)
        {
                SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                double reduce = ((totalInputSize - totalSize) * 100.00) / (double)totalInputSize;
                cout << "Compressed folder increase in: " << fixed << setprecision(2) << reduce << "%" << endl; 
        }
        else 
        {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                double increase = ((totalSize - totalInputSize) * 100.00) / (double)totalInputSize;
                cout << "Compressed folder increase in: " << fixed << setprecision(2) << increase << "%" << endl; 
        }

        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);  

}


// This function is used to decompress the file, it takes two paramter strings - which are names of input and output files.

void decompressFile (const string& inputFileName, const string &outputFileName) {

        // ifstream class reads the input file - inputFileName

        ifstream binaryInFile(inputFileName + ".bin", ios::binary);
        if(!binaryInFile)
        {
                cerr << "Error opening input file." << endl;
                return;
        }

        // As the compressed file contains Huffman codes and encoded data, their separtion is done into two strings

        string tree = "", encoded = "";
        char byte;
        bool isEncodingReading = false;

        // Huffman Codes are written into tree string and encoded data is written into encoded string
        // FILE_SPLITTER '#' helps in finding the breakpoint between them

        while (binaryInFile.read(&byte, 1))
        {
                if (!isEncodingReading) 
                {
                        if(byte == '#')
                        {
                                isEncodingReading = true;
                                continue;
                        }
                        tree += byte;
                }  
                else
                {
                    encoded += bitset<8>(byte).to_string();
                }  
        }

        binaryInFile.close();

        char ch;
        string code;
        unordered_map<string, char> charMap;
        
        // Converts tree string into string stream for reading the data

        istringstream treeInputStream(tree);

        // character Map is generated using tree

        while (treeInputStream >> ch >> code)
        {
                charMap[code] = ch;
        }

        // Decoded code is written into decoded string using the decodeFromCharMap function

        string decoded = decodeFromCharMap(encoded, charMap);

        // decode string is written into outputFileName using ofstream class

        ofstream outFile(outputFileName);
        outFile << decoded;
        outFile.close();

}



int main()
{
        // Setting up the console color.

        ios_base::sync_with_stdio(0);
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE);

        // Starting the Program

        int option;
        cout << "WELCOME TO FILE ZIPPER SOFTWARE:\n";
        cout << endl;

        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        // This Program contains 4 options to choose from as mentioned below.

        do
        {
                cout << "Choose an option:\n";
                cout << endl;
                cout << "1. Compress a file.\n";
                cout << "2. Decompress a file.\n";
                cout << "3. Demo Compress a file.\n";
                cout << "4. Exit.\n";
                cout << "Enter option (1, 2, 3 or 4): ";
                cin >> option;
                cout << endl;

            // Based on the option choosen, following switch statement is triggered.    

            switch (option)
            {
                case 1:
                {
                        // Case 1 : When user enters '1', This is triggered, it is for compression.

                        int num;
                        cout << "Enter number of files you want to compress.\n";
                        cin >> num;

                        for (int i = 1; i <= num; i++) {
                                if(i == 1) {
                                        cout << i << "st: ";
                                }
                                else if(i == 2) {
                                        cout << i << "nd: ";
                                }
                                else if(i == 3) {
                                        cout << i << "rd: " ;
                                }
                                else {
                                        cout << i << "th: ";
                                }

                                // Take input - names of input and output file from user to perform compression

                                string inputFileName, outputFileName;
                                cout << "Enter input file name: ";
                                cin >> inputFileName;
                                cout << "Enter output file name: ";
                                cin >> outputFileName;
                                cout << endl;

                                // Remove the extension (if any) from output file, to add .bin extension after it is compressed

                                int posDot = outputFileName.find_last_of(".");
                                if (posDot != string::npos) {
                                    outputFileName = outputFileName.substr(0, posDot);
                                }

                                // This function takes in both both files as paramenters and performs compression. 

                                compressFile(inputFileName, outputFileName);

                                // Once the compression is done, message in printed.

                                cout << "File compressed succesfully.\n";
                        }
                        break;
                }
                case 2:
                {
                        // Case 2 : When user enters '2', This is triggered, it is for decompression.

                        int num; 
                        cout << "Enter number of files you want to decompress." << endl;
                        cin >> num;

                        for(int i = 1; i <= num; i++)
                        {
                                if(i == 1) 
                                        cout << i << "st: ";
                                else if(i == 2)
                                        cout << i << "nd: ";
                                else if( i == 3) 
                                        cout << i << "rd: ";
                                else 
                                        cout << i << "th: ";

                                // Take input - names of input and output file from user to perform compression

                                string inputFileName, outputFileName;
                                cout << "Enter input file name: ";
                                cin >> inputFileName;
                                cout << "Enter output file name: ";
                                cin >> outputFileName;
                                cout << endl;

                                // Remove the extension (if any) from input and output file
                                // in Output file, adding .txt extension for after it is decompressed

                                int posDot = inputFileName.find_last_of(".");
                                if (posDot != string::npos) 
                                        inputFileName = inputFileName.substr(0, posDot);

                                posDot = outputFileName.find_last_of(".");
                                if (posDot == string::npos || posDot == 0) 
                                        outputFileName += ".txt";

                                // This function takes in both both files as paramenters and performs decompression.

                                decompressFile(inputFileName, outputFileName);

                                // Once the decompression is done, message in printed.

                                cout << "File decompressed succesfully.\n";
                        }
                        break;
                }
                case 3: 
                {
                         // Case 3 : When user enters '3', This is triggered, it is for demo compression.

                        int num;
                        cout << "Enter number of files you want to Demo compress." << endl;
                        cin >> num;

                        for ( int i = 1; i <= num; i++) 
                        {
                                if(i == 1)
                                        cout << i << "st: ";
                                else if(i == 2) 
                                        cout << i << "nd: ";
                                else if(i == 3) 
                                        cout << i << "rd: ";
                                else 
                                        cout << i << "th: ";
                                
                                // Take input - names of input and output file from user to perform compression

                                string inputFileName, outputFileName;
                                cout << "Enter input file name: ";
                                cin >> inputFileName;
                                cout << "Enter output file name: ";
                                cin >> outputFileName;
                                cout << endl;

                                // As here just the demo compressed file is required, which will be in txt format, this func is triggered.

                                demoCompressFile(inputFileName, outputFileName);

                                // Once the demo compression is done, message in printed.

                                cout << "Demo Compressed file created successfully.\n";
                        }
                        break;
                }
                case 4:
                {
                        // Case 4 : When user enters '4', The program is exited.

                        cout << "Exiting program.\n";
                        break;
                }
                default:
                {       
                        // In case any other input is given, this output is provided.

                        cout << "Invalid option. Please choose again.\n";
                }

            }
           

        } while (option != 4);

        // Program execution done.

        return 0;
}