#include "lex.h"
#include <regex> // we are using regex to find the tokens.
#include <cctype> // To recognize characters.

LexItem getNextToken(istream &in, int &linenumber)
{
    // State diagram for lexical analyzer
    enum State
    {
        START,
        INID,
        INSTRING,
        ININT,
        INCOMMENT
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
            if(std::isalpha(c)){
                state = INID;
                continue;
            }
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
            if(std::regex_match(lexeme + c, std::regex(identifierRegex))){
                lexeme += c;
            }
            // If end of file, or no longer IDENT
            if(in.peek() == -1 || !std::regex_match(lexeme+c,std::regex(identifierRegex))){
                state = START;
                in.putback(c); // what does this do?

                // check for reserved keywords
            }
            break;
        }


    }
    return LexItem(DONE, "", linenumber);
}