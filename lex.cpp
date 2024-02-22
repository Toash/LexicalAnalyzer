#include "lex.h"
#include <regex> // we are using regex to find the tokens.

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

            lexeme = c;

            // Comment is defined by all characters after !
            if (c == '!')
            {
                state = INCOMMENT;
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
        }
    }
    return LexItem(DONE, "", linenumber);
}