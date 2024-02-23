// Test the lexical analyzer
#include <iostream>
#include <fstream> // input file
#include <string>
#include "lex.h"

// get token name from enum

std::map<Token, std::string> tokenToString;
void populateTokenMap()
{
    tokenToString.insert(std::make_pair(IF, "IF"));
    tokenToString.insert(std::make_pair(ELSE, "ELSE"));
    tokenToString.insert(std::make_pair(PRINT, "PRINT"));
    tokenToString.insert(std::make_pair(INTEGER, "INTEGER"));
    tokenToString.insert(std::make_pair(REAL, "REAL"));
    tokenToString.insert(std::make_pair(CHARACTER, "CHARACTER"));
    tokenToString.insert(std::make_pair(END, "END"));
    tokenToString.insert(std::make_pair(THEN, "THEN"));
    tokenToString.insert(std::make_pair(PROGRAM, "PROGRAM"));
    tokenToString.insert(std::make_pair(LEN, "LEN"));
    tokenToString.insert(std::make_pair(IDENT, "IDENT"));
    tokenToString.insert(std::make_pair(ICONST, "ICONST"));
    tokenToString.insert(std::make_pair(RCONST, "RCONST"));
    tokenToString.insert(std::make_pair(SCONST, "SCONST"));
    tokenToString.insert(std::make_pair(BCONST, "BCONST"));
    tokenToString.insert(std::make_pair(PLUS, "PLUS"));
    tokenToString.insert(std::make_pair(MINUS, "MINUS"));
    tokenToString.insert(std::make_pair(MULT, "MULT"));
    tokenToString.insert(std::make_pair(DIV, "DIV"));
    tokenToString.insert(std::make_pair(ASSOP, "ASSOP"));
    tokenToString.insert(std::make_pair(EQ, "EQ"));
    tokenToString.insert(std::make_pair(POW, "POW"));
    tokenToString.insert(std::make_pair(GTHAN, "GTHAN"));
    tokenToString.insert(std::make_pair(LTHAN, "LTHAN"));
    tokenToString.insert(std::make_pair(CAT, "CAT"));
    tokenToString.insert(std::make_pair(COMMA, "COMMA"));
    tokenToString.insert(std::make_pair(LPAREN, "LPAREN"));
    tokenToString.insert(std::make_pair(RPAREN, "RPAREN"));
    tokenToString.insert(std::make_pair(DOT, "DOT"));
    tokenToString.insert(std::make_pair(DCOLON, "DCOLON"));
    tokenToString.insert(std::make_pair(DEF, "DEF"));
    tokenToString.insert(std::make_pair(ERR, "ERR"));
    tokenToString.insert(std::make_pair(DONE, "DONE"));
}
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

    populateTokenMap();

    // Repeatedly call getNextToken until it returns DONE or ERR.
    LexItem lexItem;
    int linenumber = 0;
    int tokenCount = 0;

    inFile.seekg(0); // reset input stream to beginning
    if (inFile.is_open())
    {
        while (true)
        {
            lexItem = getNextToken(inFile, linenumber);
            tokenCount++;
            // Equals operator is overridden
            if (lexItem == DONE)
            {
                break;
            }

            // error handling
            if (lexItem == ERR)
            {
                std::cout << "error on line " << linenumber;
                std::exit(1);
            }

            /*
            If the -all option is present, the program should print each token as it is read and recognized,
one token per line. The output format for the token is the token name in all capital letters (for
example, the token LPAREN should be printed out as the string LPAREN. In the case of the
IDENT, ICONST, RCONST, SCONST, and ERR tokens, the token name should be followed
by a colon and the lexeme between double quotes. For example, if an identifier “circle” and
a string literal ‘The center of the circle through these points is’ are recognized, the -all output
for them would be:

            */

            std::cout << tokenToString[lexItem.GetToken()] << ": " << lexItem.GetLexeme() << endl;
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