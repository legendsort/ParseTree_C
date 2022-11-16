#include "token.h"


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
const string LESS = "<";
const string BIG = ">";
const string PRO = "%";
const string EQ = "=";
const std::string LEFT_PARENTHESES = "(";
const std::string RIGHT_PARENTHESES = ")";
const std::string SEMI_COLON = ";";
const std::string LEFT_SQUARE_BRACKET = "[";
const std::string RIGHT_SQUARE_BRACKET = "]";

const std::string START = "begin";
const std::string END = "end";
const std::string LOOP = "loop";
const std::string VOID = "void";
const std::string VAR = "var";
const std::string RETURN = "return";
const std::string READ = "scan";
const std::string PRINT = "print";
const std::string PROGRAM = "program";
const std::string IF = "fork";
const std::string THEN = "then";
const std::string LET = "let";



Token::Token()
{
    this->typeId = DefaultTokenTypeId;
    this->value = "";
    this->line_number = 0;
}


Token::Token(TokenTypeId typeId, std::string value, int line_number)
{
    this->typeId = typeId;
    this->value = value;
    this->line_number = line_number;
}

Token::Token(TokenTypeId typeId, std::string value)
{
    this->typeId = typeId;
    this->value = value;
    this->line_number = 0;
}

Token::Token(TokenTypeId typeId, char value)
{
    std::string string_value(1, value);
    
    this->typeId = typeId;
    this->value = string_value;
    this->line_number = 0;
}

void Token::print()
{
	printf("----> %s\n", this->get_value());
}
bool Token::is_eof()
{
    return this->typeId == EndOfFileTokenId;
}

bool Token::is_identifier()
{
    return this->typeId == IdentifierTokenId;
}

bool Token::is_colon()
{
	printf("%s", this->typeId);
	return true;
}

bool Token::is_integer()
{
    return this->typeId == IntegerTokenId;
}

std::string Token::get_value()
{
    return value;
}

std::ostream& operator<<(std::ostream &stream, const Token &token)
{
    std::string token_type = get_token_type_name(token.typeId);
    return stream << token_type << "(" << token.value << ") on line " << token.line_number;
}

bool operator==(const Token &t1, const Token &t2)
{
    return t1.typeId == t2.typeId && t1.value == t2.value;
}

bool operator!=(const Token &t1, const Token &t2)
{
    return t1.typeId != t2.typeId || t1.value != t2.value;
}

bool operator<(const Token &t1, const Token &t2)
{
    return t1.value < t2.value;
}


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


bool EndOfFileToken::is_eof(std::string character)
 {
     return character[0] == EOF;
 }

EndOfFileToken::EndOfFileToken(int line_number)
: Token(EndOfFileTokenId, "EOF", line_number) {}

bool IntegerToken::is_integer(std::string character)
{
	if(character.size() == 0) return false;
	for(int i=0; i<character.size(); i++) if(!isdigit(character[i])) return false;
	return true;
}

IntegerToken::IntegerToken(std::string value, int line_number)
: Token(IntegerTokenId, value, line_number) {}


bool KeywordToken::is_keyword(std::string string)
{
    return keywords.find(string) != keywords.end();
}

bool KeywordToken::is_start_token(Token token)
{
    KeywordToken start_token = KeywordToken(START);
    return token == start_token;
}

bool KeywordToken::is_end_token(Token token)
{
    KeywordToken end_token = KeywordToken(END);
    return token == end_token;
}

bool KeywordToken::is_iter_token(Token token)
{
    KeywordToken iter_token = KeywordToken(LOOP);
    return token == iter_token;
}

bool KeywordToken::is_void_token(Token token)
{
    KeywordToken void_token = KeywordToken(VOID);
    return token == void_token;
}

bool KeywordToken::is_var_token(Token token)
{
    KeywordToken var_token = KeywordToken(VAR);
    return token == var_token;
}

bool KeywordToken::is_return_token(Token token)
{
    KeywordToken return_token = KeywordToken(RETURN);
    return token == return_token;
}

bool KeywordToken::is_read_token(Token token)
{
    KeywordToken read_token = KeywordToken(READ);
    return token == read_token;
}

bool KeywordToken::is_print_token(Token token)
{
    KeywordToken print_token = KeywordToken(PRINT);
    return token == print_token;
}

bool KeywordToken::is_program_token(Token token)
{
    KeywordToken program_token = KeywordToken(PROGRAM);
    return token == program_token;
}

bool KeywordToken::is_if_token(Token token)
{
    KeywordToken if_token = KeywordToken(IF);
    return token == if_token;
}

bool KeywordToken::is_then_token(Token token)
{
    KeywordToken then_token = KeywordToken(THEN);
    return token == then_token;
}

bool KeywordToken::is_let_token(Token token)
{
    KeywordToken let_token = KeywordToken(LET);
    return token == let_token;
}

KeywordToken::KeywordToken(std::string value, int line_number)
: Token(KeywordTokenId, value, line_number) {}

KeywordToken::KeywordToken(std::string value)
: Token(KeywordTokenId, value) {}

std::set<std::string> KeywordToken::keywords = {
    START,
    END,
    LOOP,
    VOID,
    VAR,
    RETURN,
    READ,
    PRINT,
    PROGRAM,
    IF,
    THEN,
    LET
};


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

bool OperatorToken::is_pro_token(Token token)
{
    Token pro_token = OperatorToken(PRO);
    return token == pro_token;
}

bool OperatorToken::is_eq_token(Token token)
{
    Token eq_token = OperatorToken(EQ);
    return token == eq_token;
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
    MINUS,
    PRO,
    LESS,
    BIG,
    EQ
};


bool is_token_type_id(int num)
{
    switch (num) {
        case DelimiterTokenId:
        case EndOfFileTokenId:
        case IdentifierTokenId:
        case IntegerTokenId:
        case KeywordTokenId:
        case OperatorTokenId:
        case DefaultTokenTypeId:
            return true;
        default:
            return false;
    }
}

std::string get_token_type_name(int id)
{
    switch (id) {
        case DelimiterTokenId:
            return "DelimeterToken";
        case EndOfFileTokenId:
            return "EndOfFileToken";
        case IdentifierTokenId:
            return "IdentifierToken";
        case IntegerTokenId:
            return "IntegerToken";
        case KeywordTokenId:
            return "KeywordToken";
        case OperatorTokenId:
            return "OperatorToken";
        default:
            return "DefaultToken";
    }  
}
