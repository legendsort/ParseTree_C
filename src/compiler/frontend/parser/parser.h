#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "../scanner/scanner.h"
#include "../../token/token.h"
#include "../../node/node.h"

class Parser
{
    public:
        Parser(std::string filename);
        ~Parser();
        Node* parse();

    private:
        Scanner* scanner;
        Token token;

        Node* program();
        Node* block(int level);
        Node* vars(int level);
        Node* expr(int level);
        Node* A(int level);
        Node* N(int level);
        Node* M(int level);
        Node* R(int level);
        Node* stats(int level);
        Node* mStat(int level);
        bool is_first_of_stats(Token token);
        Node* stat(int level);
        Node* in(int level);
        Node* out(int level);
        Node* ifstat(int level);
        Node* loop(int level);
        Node* assign(int level);
        Node* O(int level);
        bool is_O_token(Token token);
        void print_error_and_exit();
        void check_for_semicolon_token();
};

#endif
