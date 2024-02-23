#include "lex.h"
#include <regex>  // we are using regex to find the tokens.
#include <cctype> // To recognize characters.
#include <string>

// compare string without regard to case
bool nonCaseSensitiveEquals(std::string &a, std::string &b)
{
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

    while (in.get(c))
    {
        switch (state)
        {
        case START:
            // new lines are delimited by !
            if (c == '\n')
            {
                linenumber++;
            }

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
                // peek next char

                return LexItem(MULT, lexeme, linenumber);
            case ('/'):
                return LexItem(DIV, lexeme, linenumber);
            case ('='):
                return LexItem(ASSOP, lexeme, linenumber);
            case ('=='):
                return LexItem(EQ, lexeme, linenumber);
            case ('<'):
                return LexItem(LTHAN, lexeme, linenumber);
            case ('>'):
                return LexItem(GTHAN, lexeme, linenumber);

                // delimiters
                /*
                case (','):
                    return LexItem(COMMA, lexeme, linenumber);
                case ('('):
                    return LexItem(LPAREN, lexeme, linenumber);
                case (')'):
                    return LexItem(RPAREN, lexeme, linenumber);
                case ('.'):
                    return LexItem(DOT, lexeme, linenumber);
                case ('*'):
                    return LexItem(DEF, lexeme, linenumber);
                }
                */

                // handle operators like **, ==, //, ::

            case INCOMMENT:
                // comment lasts till end of line. does not have token.
                if (c == '\n')
                {
                    linenumber++;
                    state = START;
                }
                continue;
            case INID:
                // check if the char is valid for an identifier.
                string identifierRegex = "[a-zA-Z]([a-zA-Z]|[0-9]|_)*";
                if (std::regex_match(lexeme + c, std::regex(identifierRegex)))
                {
                    lexeme += c;
                }
                // If end of file, or no longer IDENT
                if (in.peek() == -1 || !std::regex_match(lexeme + c, std::regex(identifierRegex)))
                {
                    state = START;
                    in.putback(c); // put back into stream

                    // check for reserved keywords
                    // reserved words are NOT case sensitive
                    if (lexeme == "program")
                    {
                        return LexItem(PROGRAM, lexeme, linenumber);
                        // return LexItem
                    }
                }
                break;
            }
        }
        return LexItem(DONE, "", linenumber);
    }
}