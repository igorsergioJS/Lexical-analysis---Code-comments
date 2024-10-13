#include "lexer.h"
#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::string;
using std::stringstream;

// Implementação dos métodos do Lexer

Lexer::Lexer()
{
    in = nullptr;
    id_table["true"] = Id{ Tag::TRUE, "true" };
    id_table["false"] = Id{ Tag::FALSE, "false" };
}

Token Lexer::Scan()
{
    // Verifica se atingiu o EOF
    if (peek == EOF)
    {
        return Token{EOF};
    }

    // Salta espaços em branco e tabulações
    while (isspace(peek))
    {
        if (peek == '\n')
            line += 1;
        peek = in->get();
        if (peek == EOF)
        {
            return Token{EOF};
        }
    }

    // Ignora comentários
    if (peek == '/')
    {
        peek = in->get();
        if (peek == '/')
        {
            // Ignora até o final da linha (comentário de linha)
            while (peek != '\n' && peek != EOF)
            {
                peek = in->get();
            }
            if (peek == '\n')
            {
                line += 1;
                peek = in->get();
            }
            if (peek == EOF)
            {
                return Token{EOF};
            }
            return Scan();
        }
        else if (peek == '*')
        {
            // Ignora comentário de bloco
            peek = in->get();
            while (true)
            {
                if (peek == EOF)
                {
                    cout << "Erro: comentário de bloco não terminado.";
                    exit(1);
                }
                if (peek == '*')
                {
                    peek = in->get();
                    if (peek == '/')
                    {
                        peek = in->get(); // Consumir '/'
                        break;
                    }
                }
                else
                {
                    if (peek == '\n')
                    {
                        line += 1;
                    }
                    peek = in->get();
                }
            }
            if (peek == EOF)
            {
                return Token{EOF};
            }
            return Scan();
        }
        else
        {
            // Não é um comentário, é um operador de divisão
            Token t{'/'};
            cout << "<" << char(t.tag) << "> ";
            // peek já está no próximo caractere
            return t;
        }
    }

    // Retorna números
    if (isdigit(peek))
    {
        int v = 0;
        do
        {
            int n = peek - '0';
            v = 10 * v + n;
            peek = in->get();
        }
        while (isdigit(peek));
        cout << "<NUM," <<  v << "> ";
        return Num{v};
    }

    // Retorna palavras-chave e identificadores
    if (isalpha(peek))
    {
        stringstream ss;
        do
        {
            ss << char(peek); // Converte int para char
            peek = in->get();
        }
        while (isalpha(peek));
        string s = ss.str();
        auto pos = id_table.find(s);
        if (pos != id_table.end())
        {
            switch (pos->second.tag)
            {
            case TRUE: cout << "<" << "TRUE" << "," << pos->second.name << "> "; break;
            case FALSE: cout << "<" << "FALSE" << "," << pos->second.name << "> "; break;
            default: cout << "<" << "ID" << "," << pos->second.name << "> "; break;
            }
            return pos->second;
        }
        Id new_id {Tag::ID, s};
        id_table[s] = new_id;
        cout << "<" << "ID" << "," << new_id.name << "> ";
        return new_id;
    }

    // Operadores e caracteres não alfanuméricos isolados
    if (peek == EOF)
    {
        return Token{EOF};
    }

    Token t {peek};
    cout << "<" << char(t.tag) << "> ";
    peek = in->get();
    return t;
}

void Lexer::Start()
{
    string input_line;
    string input_text;

    while (true)
    {
        std::getline(cin, input_line);
        if (input_line.empty())
        {
            break; // Linha em branco sinaliza o fim da entrada
        }
        input_text += input_line + '\n';
    }

    // Cria um stringstream a partir da entrada acumulada
    std::istringstream iss(input_text);
    in = &iss; // Define o fluxo de entrada para o stringstream

    peek = in->get();
    while (true)
    {
        if (peek == EOF)
            break;
        Token tok = Scan();
        if (tok.tag == EOF)
            break;
    }
}
