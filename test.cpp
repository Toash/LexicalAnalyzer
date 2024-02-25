// Test the lexical analyzer
#include <iostream>
#include <fstream> // input file
#include <string>
#include "lex.h"
#include <unordered_set>

// tokens we have (non duplicate)
std::unordered_set<Token> tokensWeHave; 
std::unordered_set<string> identifiersWeHave;

// get token name from enum
std::map<Token, std::string> tokenToString = {
    {IF, "IF"},
        {ELSE, "ELSE"},
        {PRINT, "PRINT"},
        {INTEGER, "INTEGER"},
        {REAL, "REAL"},
        {CHARACTER, "CHARACTER"},
        {END, "END"},
        {THEN, "THEN"},
        {PROGRAM, "PROGRAM"},
        {LEN, "LEN"},
        {IDENT, "IDENT"},
        {ICONST, "ICONST"},
        {RCONST, "RCONST"},
        {SCONST, "SCONST"},
        {BCONST, "BCONST"},
        {PLUS, "PLUS"},
        {MINUS, "MINUS"},
        {MULT, "MULT"},
        {DIV, "DIV"},
        {ASSOP, "ASSOP"},
        {EQ, "EQ"},
        {POW, "POW"},
        {GTHAN, "GTHAN"},
        {LTHAN, "LTHAN"},
        {CAT, "CAT"},
        {COMMA, "COMMA"},
        {LPAREN, "LPAREN"},
        {RPAREN, "RPAREN"},
        {DOT, "DOT"},
        {DCOLON, "DCOLON"},
        {DEF, "DEF"},
        {ERR, "ERR"},
        {DONE, "DONE"}
    };

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
    LexItem lexItem;
    int linenumber = 0;
    int tokenCount = 0;
    int identCount = 0;
    int intCount = 0;
    int realCount = 0;
    int stringCount = 0;

    inFile.seekg(0); // reset input stream to beginning
    if (inFile.is_open())
    {
        while (true)
        {
            
            lexItem = getNextToken(inFile, linenumber);
            
            // Equals operator is overridden, will compare token.
            if (lexItem == DONE)
            {
                //std::cout<<"DONE!!!!!"<<std::endl;
                break;
            }

            // error handling
            if (lexItem == ERR)
            {
                std::cout << "error on line " << linenumber;
                std::exit(1);
            }

            // we are counting all tokens except for the done token
            if(lexItem.GetToken() != DONE) tokenCount++;   

            // Check what kind of token it is so we can do the necessary output
            switch(lexItem.GetToken()){
                
                 
                case IDENT:
                    identifiersWeHave.insert(lexItem.GetLexeme());
                    std::cout << tokenToString[lexItem.GetToken()] << ": " << '\''<<lexItem.GetLexeme()<<'\'' << endl;
                    continue;
                case ICONST:
                    intCount++;
                    continue;
                case RCONST:
                    realCount++;
                    continue;
                case SCONST:
                    stringCount++;
                    continue;
                default:
                    std::cout << tokenToString[lexItem.GetToken()] << std::endl;
            }
                   
            
        }
    }
    else
    {
        std::cout << "NO SPECIFIED INPUT FILE.\n";
        exit(1);
    }

    // Summary info
    std::cout<<std::endl;
    std::cout << "Lines: " << linenumber << std::endl;
    std::cout << "Total Tokens: " << tokenCount << std::endl; 
    std::cout << "Identifiers: " << identifiersWeHave.size()<< std::endl;
    std::cout << "Integers: " << intCount<<std::endl;
    std::cout << "Reals: " << realCount<<std::endl;
    std::cout << "Strings: " << stringCount<<std::endl;
    return 0;
}