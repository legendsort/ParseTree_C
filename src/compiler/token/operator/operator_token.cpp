#include <string>
#include "operator_token.h"

#include <bits/stdc++.h>


using namespace std;
const string ADDITION = "++";
const string SUBTRACTION = "--";
const string DIVISION = "/";
const string MULTIPLY = "*";
const string NEGATION = "--";
const string LESS_THAN = "<=";
const string GREATER_THAN = ">=";
const string ASSIGNMENT = "==";
const string EQUALS = ":";
const string ENDLINE = ";";
const string PLUS = "+";
const string MINUS = "-";

bool OperatorToken::is_operator(string character)
{
    return operators.find(character) != operators.end();
}

bool OperatorToken::is_addition_token(Token token)
{
    Token addition_token = OperatorToken(ADDITION);
    return token == addition_token;
}

bool OperatorToken::is_subtraction_token(Token token)
{
    Token subtraction_token = OperatorToken(SUBTRACTION);
    return token == subtraction_token;
}

bool OperatorToken::is_multiplication_token(Token token)
{
    Token multiplication_token = OperatorToken(MULTIPLY);
    return token == multiplication_token;
}

bool OperatorToken::is_division_token(Token token)
{
    Token division_token = OperatorToken(DIVISION);
    return token == division_token;
}

bool OperatorToken::is_negation_token(Token token)
{
    Token negation_token = OperatorToken(NEGATION);
    return token == negation_token;
}

bool OperatorToken::is_less_than_token(Token token)
{
    Token less_than_token = OperatorToken(LESS_THAN);
    return token == less_than_token;
}

bool OperatorToken::is_greater_than_token(Token token)
{
    Token greater_than_token = OperatorToken(GREATER_THAN);
    return token == greater_than_token;
}

bool OperatorToken::is_equals_token(Token token)
{
    Token equals_token = OperatorToken(EQUALS);
    return token == equals_token;
}

bool OperatorToken::is_assignment_token(Token token)
{
    Token assignment_token = OperatorToken(ASSIGNMENT);
    return token == assignment_token;
}

bool OperatorToken::is_endline_token(Token token)
{
    Token endline_token = OperatorToken(ENDLINE);
    return token == endline_token;
}


OperatorToken::OperatorToken(std::string value, int line_number)
: Token(OperatorTokenId, value, line_number) {}

OperatorToken::OperatorToken(string value)
: Token(OperatorTokenId, value) {}

std::set<string> OperatorToken::operators = {
    ADDITION,
    SUBTRACTION,
    DIVISION,
    NEGATION,
    LESS_THAN,
    GREATER_THAN,
    EQUALS,
    ASSIGNMENT,
    ENDLINE,
    MULTIPLY,
    PLUS,
    MINUS
};
