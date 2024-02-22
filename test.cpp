// Test the lexical analyzer
#include <iostream>
#include <fstream> // input file
#include <string>
#include "lex.h"

/*
● -all (optional): if present, every token is printed out when it is seen followed by its lexeme
using the format described below.
● -int (optional): if present, prints out all the unique integer constants in numeric order.
● -real (optional): if present, prints out all the unique real constants in numeric order.
● -str (optional): if present, prints out all the unique string constants in order
● -id (optional): if present, prints out all of the unique identifiers in alphanumeric order. Each
identifier is followed by the number of its occurrences between parentheses.
● -kw (optional): if present, prints out all of the unique keywords in alphabetical order. Each
keyword is followed by the number of its occurrences between parentheses.
● filename argument must be passed to main function. Your program should open the file
and read from that filename.
*/

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "NO SPECIFIED INPUT FILE.\n";
        exit(1);
    }

    std::string fileName = argv[1];
    std::ifstream inFile;
    inFile.open(fileName);
    if (inFile.fail())
    {
        std::cout << "CANNOT OPEN THE FILE: ";
        std::cout << fileName << std::endl;
        exit(1);
    }

    inFile.seekg(0, std::ios::end);
    if (inFile.tellg() == 0)
    {
        std::cout << "File is empty.\n";
        exit(1);
    }

    // Repeatedly call getNextToken until it returns DONE or ERR.
    LexItem token;
    int linenumber = 0;
    int tokenCount = 0;

    inFile.seekg(0); // reset input stream to beginning
    if (inFile.is_open())
    {
        while (true)
        {
            token = getNextToken(inFile, linenumber);
            tokenCount++;
            // Equals operator is overridden
            if (token == DONE)
            {
                break;
            }

            // error handling
            if (token == ERR)
            {
                std::cout << "error on line " << linenumber;
                std::exit(1);
            }
            // std::cout << token;
        }
    }
    else
    {
        std::cout << "NO SPECIFIED INPUT FILE.\n";
        exit(1);
    }

    // Summary info
    std::cout << "Lines: " << linenumber << std::endl;
    std::cout << "Total Tokens: " << tokenCount << std::endl;
    std::cout << "Identifiers: " << std::endl;
    std::cout << "Integers: " << std::endl;
    std::cout << "Reals: " << std::endl;
    std::cout << "Strings: " << std::endl;
    return 0;
}