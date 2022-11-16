#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

#include "token.h"

const std::string START = "program";
const std::string BLOCK = "block";
const std::string VARS = "vars";
const std::string EXPR = "exp";
const std::string HASH = "H";
const std::string A_LETTER = "A";
const std::string R_LETTER = "R";
const std::string M_LETTER = "M";
const std::string N_LETTER = "N";
const std::string STATS = "stats";
const std::string M_STAT = "mStat";
const std::string STAT = "stat";
const std::string IN = "in";
const std::string OUT = "out";
const std::string IFSTAT = "ifstat";
const std::string LOOP = "loop";
const std::string ASSIGN = "assign";
const std::string OPERATOR = "O";

class Node
{
    public:
        static Node* of(std::string label, int level);
        static void destroy(Node* node);
        void append_child(Node* child);
        void append_token(Token token);
        static void print(Node* node);
        std::vector<Token> get_identifier_tokens();
        std::vector<Node*> children;
        std::string label;
        std::vector<Token> tokens;
        int level;
    
    private:
        static void print_node(Node* node);
        static void print_children(Node* node);
        friend std::ostream& operator<<(std::ostream&, const Node&);
};

#endif
