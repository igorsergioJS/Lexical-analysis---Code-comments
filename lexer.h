#ifndef LEXER_H
#define LEXER_H

#include <unordered_map>
#include <string>
#include <istream>

// Enumeração para tags dos tokens
enum Tag { NUM = 256, ID, TRUE, FALSE };

// Estruturas de tokens
struct Token
{
    int tag;
    Token(int t) : tag(t) {}
};

struct Num : public Token
{
    int value;
    Num(int v) : Token(Tag::NUM), value(v) {}
};

struct Id : public Token
{
    std::string name;
    Id() : Token(0) {}
    Id(int t, const std::string& s) : Token(t), name(s) {}
};

// Classe Lexer
class Lexer
{
private:
    int  line = 1;
    int peek = ' '; // Alterado para int
    std::unordered_map<std::string, Id> id_table;
    std::istream* in; // Fluxo de entrada

public:
    Lexer();
    Token Scan();
    void Start();
};

#endif // LEXER_H
