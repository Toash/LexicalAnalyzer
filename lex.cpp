#include "lex.h"
#include <regex>  // we are using regex to find the tokens.
#include <cctype> // To recognize characters.
#include <string>

/*
bool isDelimiter(char c){
    return(c==' ' || c=='\n')
}
*/

// map string value of keyword to its token;
std::map<string, Token> stringToKeyword = {
    {"if", IF},
    {"else", ELSE},
    {"print", PRINT},
    {"integer", INTEGER},
    {"real", REAL},
    {"character", CHARACTER},
    {"end", END},
    {"then", THEN},
    {"program", PROGRAM},
    {"len", LEN},
    {"ident", IDENT},
    {"iconst", ICONST},
    {"rconst", RCONST},
    {"sconst", SCONST},
    {"bconst", BCONST}};

LexItem id_or_kw(const string &lexeme, int linenum)
{
    // TODO: Make it case insensitive
    if (stringToKeyword.find(lexeme) != stringToKeyword.end())
    {
        // keyword
        return LexItem(stringToKeyword[lexeme], lexeme, linenum);
    }
    else
    {
        // identifier
        return LexItem(IDENT, lexeme, linenum);
    }
}

LexItem getNextToken(istream &in, int &linenumber)
{
    // State diagram for lexical analyzer
    enum State
    {
        START,
        INID,
        INSTRING,
        ININT,
        INREAL,
        INCOMMENT,
        INSIGN
    };
    State state = START;
    string lexeme;
    char c;

    string identifierRegex = "[a-zA-Z]([a-zA-Z]|[0-9]|_)*";
    string intRegex = "[0-9]+";
    string realRegex = "([0-9]*)\\.([0-9]+)";
    char delimitType;

    while (in.get(c))
    {
        if (c == '\n')
        {
            linenumber++;
        }
        switch (state)
        {
        case START:
            // new lines are delimited by !

            if (std::isspace(c))
            {
                continue;
            }

            // start building our lexeme
            lexeme = c;

            // Comment is defined by all characters after !
            if (c == '!')
            {
                state = INCOMMENT;
                continue;
            }

            // Recognizing IDENT
            if (std::isalpha(c))
            {
                state = INID;
                continue;
            }
            // Recognizing integer
            if (std::isdigit(c))
            {
                state = ININT;

                continue;
            }
            // recognize single chars
            switch (c)
            {
            case ('+'):
                return LexItem(PLUS, lexeme, linenumber);
            case ('-'):
                return LexItem(MINUS, lexeme, linenumber);
            case ('*'):
                // peek next char to check for power (**)

                return LexItem(MULT, lexeme, linenumber);
            case ('/'):
                return LexItem(DIV, lexeme, linenumber);
            case ('='):
                // peek next char to check for ==
                return LexItem(ASSOP, lexeme, linenumber);

            case ('<'):
                return LexItem(LTHAN, lexeme, linenumber);
            case ('>'):
                return LexItem(GTHAN, lexeme, linenumber);

            case (','):
                return LexItem(COMMA, lexeme, linenumber);
            case ('('):
                return LexItem(LPAREN, lexeme, linenumber);
            case (')'):
                return LexItem(RPAREN, lexeme, linenumber);
            case ('.'):
                // for example, .5
                if (isdigit(in.peek()))
                {
                    state = INREAL;
                    continue;
                }
                else
                {
                    return LexItem(DOT, lexeme, linenumber);
                }

            case ('\"'):
                state = INSTRING;
            case ('\''):
                state = INSTRING;
            }

        case INID:
            // check if the char is valid for an identifier.
            // std::cout<<"IN IDENT STATE!!\n";
            if (std::regex_match(lexeme + c, std::regex(identifierRegex)))
            {
                lexeme += c;
            }
            else
            {
                state = START;
                in.putback(c);
                return id_or_kw(lexeme, linenumber);
            }
            continue;
        //  1 or more integer
        case ININT:

            if (std::regex_match(lexeme + c, std::regex(intRegex)))
            {
                lexeme += c;
            }
            else if (c == '.') // we have a real number!
            {
                lexeme += c;
                state = INREAL;
            }
            else if (c == ' ' || c == '\n')
            { // delimited
                return LexItem(ICONST, lexeme, linenumber);
            }
            continue;

        case INREAL:

            if (std::regex_match(lexeme + c, std::regex(realRegex)))
            {
                lexeme += c;
                continue;
            }
            else
            {
                if (c == ' ' || c == '\n')
                {
                    return LexItem(RCONST, lexeme, linenumber);
                }
                else // we  have something else
                {
                    return LexItem(ERR, lexeme + c, linenumber);
                }
            }
        case INSTRING:

            delimitType = lexeme[0];

            // Strings must be on the same line
            if (c == '\n')
            {
                // return LexItem(ERR, lexeme, linenumber);
            }

            if (delimitType == '\'')
            {
                if (c == '\'')
                {
                    lexeme += c;
                    return LexItem(SCONST, lexeme, linenumber);
                }
            }
            else if (delimitType == '\"')
            {
                if (c == '\"')
                {
                    lexeme += c;
                    return LexItem(SCONST, lexeme, linenumber);
                }
            }

        case INCOMMENT:
            // comment lasts till end of line. does not have token.
            if (c == '\n')
            {
                state = START;
            }
            continue;
        }
    }
    // this returns once we exhaust the istream
    return LexItem(DONE, "", linenumber);
}
