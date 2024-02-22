#include "lex.h"

LexItem getNextToken(istream &in, int &linenumber)
{

    // State diagram for lexical analyzer
    enum State
    {
        START,
        INID
    } char c;
    while (in.get(c))
    {
        // Recognize the lexemes (with a corresponding token)
        //      To produce a LexItem.
    }
}