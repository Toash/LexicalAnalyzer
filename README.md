Lexical Analyzer assignment for CS 280

Given a file, finds all the lexemes and categorizes them to the respective tokens. Has multiple options for displaying the lexemes and their tokens.

Reserved Words and their respective Token:

| Reserved Words | Tokens   |
|----------------|----------|
| program        | PROGRAM  |
| end            | END      |
| else           | ELSE     |
| if             | IF       |
| integer        | INTEGER  |
| real           | REAL     |
| character      | CHARACTER|
| print          | PRINT    |
| len            | LEN      |

Operator Symbols and their respective Token:

| Operator  Symbol | Token | Description                          |
|------------|--------|---------------------------------------------|
| +          | PLUS   | Arithmetic addition or concatenation |
| -          | MINUS  | Arithmetic subtraction                |
| *          | MULT   | Multiplication                       |
| /          | DIV    | Division                             |
| **         | POW    | Exponentiation                       |
| =          | ASSOP  | Assignment operator                  |
| ==         | EQ     | Equality                             |
| <          | LTHAN  | Less than operator                   |
| >          | GTHAN  | Greater than operator                |
| //         | CAT    | Concatenation                        |

Character(s) and their respective Token:

| Character | Token  | Description           |
|-----------|--------|-----------------------|
| ,         | COMMA  | Comma                 |
| (         | LPAREN | Left Parenthesis      |
| )         | RPAREN | Right Parenthesis     |
| ::        | DCOLON | Double Colons         |
| .         | DOT    | Dot                   |
| *         | DEF    | Default mark          |

The program accepts optional flags, which affects what will be printed. Flags should be specified after the file name, and the file name should be the first argument.

| Option   | Description                                                                        |
|----------|------------------------------------------------------------------------------------|
| -all     | If present, every token is printed out when it is seen followed by its lexeme      |
| -int     | If present, prints out all the unique integer constants in numeric order           |
| -real    | If present, prints out all the unique real constants in numeric order              |
| -str     | If present, prints out all the unique string constants in order                    |
| -id      | If present, prints out all of the unique identifiers in alphanumeric order         |
| -kw      | If present, prints out all of the unique keywords in alphabetical order            |

