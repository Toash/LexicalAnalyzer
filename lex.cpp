#include "lex.h"

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
    char c;
    while (in.get(c))
    {
        switch (state)
        {
        case START:
            // new lines are delimited by !
            if (c = '\n')
            {
                linenumber++;
            }

            if (std::isspace(c))
            {
                continue;
            }

            // Comment is defined by all characters after !
            if (c == '!')
            {
                state = INCOMMENT;
                continue
            }
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