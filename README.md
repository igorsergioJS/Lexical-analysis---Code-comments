# Lexical-analysis---Code-comments
Laboratório 01 - Análise Léxica: Ampliação de um analisador léxico para lidar com comentários de código.

Foi utilizado como código-base o analisador léxico disponibilizado no material de laboratório 10 de Compiladores do professor Judson Santos Santiago. [Link aqui](https://github.com/JudsonSS/Compiladores).

O Lexer agora:

- Ignora corretamente comentários de linha e de bloco, independentemente de se estenderem por múltiplas linhas.

- Processa múltiplas linhas de entrada, permitindo que o usuário insira todo o código desejado antes de iniciar o processamento, encerrando a entrada ao inserir uma linha em branco.

- Lida adequadamente com o EOF, evitando erros e a impressão de caracteres inválidos ao final da entrada.
