// Test the lexical analyzer
#include <iostream>
#include <fstream> // input file
#include <string>
#include "lex.h"
#include <unordered_set>
#include <set>

// When counting lexemes, we shouldn't consider duplicates -_-...
std::set<Token> tokensWeHave;
std::set<string> identifiersWeHave;
std::set<int> integersWeHave;

std::unordered_set<string> flags;

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
    {DONE, "DONE"}};

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
    if (argc > 2)
    { // we have optional parameters!
        for (int i = 2; i < argc; i++)
        {
            flags.insert(argv[i]);
        }
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
    int linenumber = 1; // lines are 1 indexed.
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
                // std::cout<<"DONE!!!!!"<<std::endl;
                break;
            }

            // we are counting all tokens except for the done token
            if (lexItem.GetToken() != DONE)
                tokenCount++;

            // Check what kind of token it is so we can do the necessary output
            switch (lexItem.GetToken())
            {
            case IDENT:
                identifiersWeHave.insert(lexItem.GetLexeme());
                std::cout << tokenToString[lexItem.GetToken()] << ": " << '\'' << lexItem.GetLexeme() << '\'' << endl;
                continue;
            case ICONST:
                integersWeHave.insert(std::stoi(lexItem.GetLexeme()));
                std::cout << tokenToString[lexItem.GetToken()] << ": " << '(' << lexItem.GetLexeme() << ')' << endl;
                continue;
            case RCONST:
                realCount++;
                std::cout << tokenToString[lexItem.GetToken()] << ": " << '(' << lexItem.GetLexeme() << ')' << endl;
                continue;
            case SCONST:
                stringCount++;
                continue;
            case ERR:
                std::cout << "Error in line " << lexItem.GetLinenum() << ": Unrecognized Lexeme {" << lexItem.GetLexeme() << "}" << endl;
                std::exit(1);
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
    std::cout << std::endl;
    std::cout << "Lines: " << linenumber - 1 << std::endl; // line numbers are 1 indexed.
    std::cout << "Total Tokens: " << tokenCount << std::endl;
    std::cout << "Identifiers: " << identifiersWeHave.size() << std::endl;
    std::cout << "Integers: " << integersWeHave.size() << std::endl;
    std::cout << "Reals: " << realCount << std::endl;
    std::cout << "Strings: " << stringCount << std::endl;

    // idents
    if (auto flag = flags.find("-id") != flags.end())
    {
        std::cout << "IDENTIFIERS:\n";
    }
    // keywords
    if (auto flag = flags.find("-kw") != flags.end())
    {
        std::cout << "KEYWORDS:\n";
    }
    // integers
    if (auto flag = flags.find("-int") != flags.end())
    {
        std::cout << "INTEGERS:\n";
        for (auto it = integersWeHave.begin(); it != integersWeHave.end(); it++)
        {
            if (std::next(it) == integersWeHave.end())
            {
                std::cout << *it << std::endl;
            }
            else
            {
                std::cout << *it << ", ";
            }
        }
    }
    // real
    if (auto flag = flags.find("-real") != flags.end())
    {
        std::cout << "REALS:\n";
    }
    // strings
    if (auto flag = flags.find("-str") != flags.end())
    {
        std::cout << "STRINGS:\n";
    }

    return 0;
}