// Test the lexical analyzer
#include <iostream>
#include <fstream> // input file
#include <string>
#include "lex.h"
#include <unordered_set>
#include <set>
#include <map>

// When counting lexemes, we shouldn't consider duplicates -_-...
std::set<Token> tokensWeHave;
std::map<string, int> identifierCount;
std::set<int> integersWeHave;
std::set<double> realsWeHave;
std::set<string> stringsWeHave;
std::map<string, int> keywordsCount;

std::unordered_set<string> flags;

int main(int argc, char *argv[])
{
    std::ifstream inFile;
    if (argc == 1)
    {
        std::cout << "NO SPECIFIED INPUT FILE.\n";
        exit(1);
    }
    if (argc > 2)
    { // we have optional parameters!
        for (int i = 2; i < argc; i++)
        {

            string arg = argv[i];
            // check for mulitple files
            inFile.open(arg);
            if (inFile)
            {
                std::cout << "ONLY ONE FILE NAME IS ALLOWED" << endl;
                std::exit(1);
            }
            // check for bad flags.
            if (arg != "-all" || arg != "-int" || arg != "-real" || arg != "-str" || arg != "-id" || arg != "-kw")
            {
                std::cout << "UNRECOGNIZED FLAG {" << arg << "}" << endl;
                exit(1);
            }
            flags.insert(arg);
        }
    }

    std::string fileName = argv[1];

    inFile.open(fileName);
    if (inFile.fail())
    {
        std::cout << "CANNOT OPEN THE FILE ";
        std::cout << fileName << std::endl;
        exit(1);
    }

    inFile.seekg(0, std::ios::end);
    if (inFile.tellg() == 0)
    {
        std::cout << "Empty File.\n";
        exit(1);
    }

    // Repeatedly call getNextToken until it returns DONE or ERR.
    LexItem lexItem;
    int linenumber = 1; // lines are 1 indexed.
    int tokenCount = 0;

    inFile.seekg(0); // reset input stream to beginning
    if (inFile.is_open())
    {
        while (true)
        {

            lexItem = getNextToken(inFile, linenumber);

            // Equals operator is overridden, will compare token.
            if (lexItem == DONE)
            {
                break;
            }

            tokenCount++;

            if (auto it = flags.find("-all") != flags.end())
            {
                std::cout << lexItem; // we overloaded to << operator!
            }

            // Check what kind of token it is so we can do the necessary output
            switch (lexItem.GetToken())
            {
            case IDENT:
                // add to count map
                identifierCount[lexItem.GetLexeme()]++;
                continue;
            case ICONST:
                integersWeHave.insert(std::stoi(lexItem.GetLexeme()));
                continue;
            case RCONST:
                realsWeHave.insert(std::stod(lexItem.GetLexeme()));
                continue;
            case SCONST:
                stringsWeHave.insert(lexItem.GetLexeme());
                continue;
            case IF:
            case ELSE:
            case PRINT:
            case INTEGER:
            case REAL:
            case CHARACTER:
            case END:
            case THEN:
            case PROGRAM:
            case LEN:
                keywordsCount[lexItem.GetLexeme()]++;
                continue;
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
    std::cout << "Identifiers: " << identifierCount.size() << std::endl;
    std::cout << "Integers: " << integersWeHave.size() << std::endl;
    std::cout << "Reals: " << realsWeHave.size() << std::endl;
    std::cout << "Strings: " << stringsWeHave.size() << std::endl;

    // idents
    if (auto flag = flags.find("-id") != flags.end())
    {
        std::cout << "IDENTIFIERS:\n";
        for (auto it = identifierCount.begin(); it != identifierCount.end(); it++)
        {
            if (std::next(it) == identifierCount.end())
            {
                std::cout << it->first << " (" << it->second << ")" << endl;
            }
            else
            {
                std::cout << it->first << " (" << it->second << "), ";
            }
        }
    }
    // keywords
    if (auto flag = flags.find("-kw") != flags.end())
    {
        std::cout << "KEYWORDS:\n";
        for (auto it = keywordsCount.begin(); it != keywordsCount.end(); it++)
        {
            if (std::next(it) == keywordsCount.end())
            {
                std::cout << it->first << " (" << it->second << ")" << endl;
            }
            else
            {
                std::cout << it->first << " (" << it->second << "), ";
            }
        }
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
        for (auto it = realsWeHave.begin(); it != realsWeHave.end(); it++)
        {
            if (std::next(it) == realsWeHave.end())
            {
                std::cout << *it << std::endl;
            }
            else
            {
                std::cout << *it << ", ";
            }
        }
    }
    // strings
    if (auto flag = flags.find("-str") != flags.end())
    {
        std::cout << "STRINGS:\n";
        for (auto it = stringsWeHave.begin(); it != stringsWeHave.end(); it++)
        {
            string output = *it;
            output = output.substr(1, output.size() - 2);
            if (std::next(it) == stringsWeHave.end())
            {
                std::cout << "\"" << output << "\"" << std::endl;
            }
            else
            {
                std::cout << *it << ", ";
            }
        }
    }

    return 0;
}