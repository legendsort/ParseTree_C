#include "delimiter_token.h"

#include <string>
#include <bits/stdc++.h>

using namespace std;

const std::string LEFT_PARENTHESES = "(";
const std::string RIGHT_PARENTHESES = ")";
const std::string SEMI_COLON = ";";
const std::string LEFT_SQUARE_BRACKET = "[";
const std::string RIGHT_SQUARE_BRACKET = "]";

bool DelimiterToken::is_delimiter(std::string character)
{
    return delimiters.find(character) != delimiters.end();
}


bool DelimiterToken::is_left_parentheses_token(Token token)
{
    Token left_parentheses_token = DelimiterToken(LEFT_PARENTHESES);
    return token == left_parentheses_token;
}

bool DelimiterToken::is_right_parentheses_token(Token token)
{
    Token right_parentheses_token = DelimiterToken(RIGHT_PARENTHESES);
    return token == right_parentheses_token;
}

bool DelimiterToken::is_semi_colon_token(Token token)
{	
    Token semi_colon_token = DelimiterToken(SEMI_COLON);
    return token.get_value() == semi_colon_token.get_value();
}


bool DelimiterToken::is_left_square_bracket_token(Token token)
{
    Token left_square_bracket_token = DelimiterToken(LEFT_SQUARE_BRACKET);
    return token == left_square_bracket_token;
}

bool DelimiterToken::is_right_square_bracket_token(Token token)
{
    Token right_square_bracket_token = DelimiterToken(RIGHT_SQUARE_BRACKET);
    return token == right_square_bracket_token;
}

DelimiterToken::DelimiterToken(std::string value, int line_number)
: Token(DelimiterTokenId, value, line_number) {}

DelimiterToken::DelimiterToken(std::string value)
: Token(DelimiterTokenId, value) {}

std::set<std::string> DelimiterToken::delimiters = {
    LEFT_PARENTHESES,
    RIGHT_PARENTHESES,
    SEMI_COLON,
    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET
};
