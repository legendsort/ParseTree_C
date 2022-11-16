#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <fstream>
#include <set>
#include <bits/stdc++.h>
using namespace std;

typedef enum {
    DelimiterTokenId = 1000,
    EndOfFileTokenId = 1001,
    IdentifierTokenId = 1002,
    IntegerTokenId = 1003,
    KeywordTokenId = 1004,
    OperatorTokenId = 1005,
    DefaultTokenTypeId = 1006
} TokenTypeId;

class Token
{
    public:
        Token();
        Token(TokenTypeId typeId, std::string value, int line_number);
        Token(TokenTypeId typeId, std::string value);
        Token(TokenTypeId typeId, char value);
        bool is_eof();
        bool is_identifier();
        bool is_integer();
        bool is_colon();
        void print();
        std::string get_value();
        
    private:
        TokenTypeId typeId;
        std::string value;
        int line_number;
        friend std::ostream& operator<<(std::ostream&, const Token&);
        friend bool operator==(const Token&, const Token&);
        friend bool operator!=(const Token&, const Token&);
        friend bool operator<(const Token&, const Token&);
};

class DelimiterToken : public Token
{
    public:
        static bool is_delimiter(std::string character);
        static bool is_left_parentheses_token(Token token);
        static bool is_right_parentheses_token(Token token);
        static bool is_semi_colon_token(Token token);
        static bool is_left_square_bracket_token(Token token);
        static bool is_right_square_bracket_token(Token token);
        DelimiterToken(std::string value, int line_number);
        DelimiterToken(std::string value);

    private:
        static std::set<std::string> delimiters;
};

class EndOfFileToken : public Token
{
    public:
        static bool is_eof(std::string character);
        EndOfFileToken(int line_number);
};

class IdentifierToken : public Token
{
    public:
        static bool is_identifier(Token token);
        IdentifierToken(std::string value, int line_number) : Token(IdentifierTokenId, value, line_number) {}
};

class IntegerToken : public Token
{
    public:
        static bool is_integer(std::string character);
        IntegerToken(std::string value, int line_number);
};

class KeywordToken : public Token
{
    public:
        static bool is_keyword(std::string string);
        static bool is_start_token(Token token);
        static bool is_end_token(Token token);
        static bool is_iter_token(Token token);
        static bool is_void_token(Token token);
        static bool is_var_token(Token token);
        static bool is_return_token(Token token);
        static bool is_read_token(Token token);
        static bool is_print_token(Token token);
        static bool is_program_token(Token token);
        static bool is_if_token(Token token);
        static bool is_then_token(Token token);
        static bool is_let_token(Token token);
        KeywordToken(std::string value, int line_number);
        KeywordToken(std::string value);

    private:
        static std::set<std::string> keywords;
};

class OperatorToken : public Token
{
    public:
        static bool is_operator(std::string character);
        static bool is_addition_token(Token token);
        static bool is_subtraction_token(Token token);
        static bool is_multiplication_token(Token token);
        static bool is_division_token(Token token);
        static bool is_negation_token(Token token);
        static bool is_less_than_token(Token token);
        static bool is_greater_than_token(Token token);
        static bool is_equals_token(Token token);
        static bool is_assignment_token(Token token);
        static bool is_endline_token(Token token);
        static bool is_pro_token(Token token);
        static bool is_eq_token(Token token);
        OperatorToken(std::string value, int line_number);
        OperatorToken(char value);
        OperatorToken(std::string value);

    private:
        static std::set<std::string> operators;
};


bool is_token_type_id(int num);

std::string get_token_type_name(int id);



#endif
