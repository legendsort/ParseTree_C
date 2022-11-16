#include <fstream>
#include <iostream>
#include <string>

#include "scanner.h"
#include <bits/stdc++.h>

using namespace std;

#define COMMENT_CHAR '!'
#define COMMENT_STATE 9

Scanner::Scanner(std::string filename)
{
    file.open(filename);
    check_file(file, filename);
    line_number = 1;
    next_char = ' ';
    is_eof_reached = false;
}

Scanner::~Scanner()
{
    close_file();
}

void Scanner::check_file(std::ifstream& file, std::string filename)
{
    if (!file) {
        exit(1);
    }
}

void Scanner::close_file()
{
    file.close();
}


Token Scanner::read()
{
    int state = 0;
    std::string s = "";
	s += next_char;
    int next_state = StateTransitionTable::get_next_state(state, s);
    std::string string = "";
    
    do {
    	s = "";
		s += next_char;
        check_for_eof();
        
        check_for_invalid_character(state);

        next_state = StateTransitionTable::get_next_state(state, s);
        if (StateTransitionTable::is_final_state(next_state)) {
            return StateTransitionTable::get_token(next_state, string, line_number);
        } else {
            state = next_state;
            if (!isspace(next_char)) {
                string += next_char;
            }
            
        }
        if (next_char == '\n') {
            line_number++;
        }
    } while (file >> std::noskipws >> next_char || !is_eof_reached);

    return EndOfFileToken(line_number);
}

void Scanner::check_for_invalid_character(int state)
{
	std::string s = ""; s += next_char;
    if (StateTransitionTable::is_invalid_char(std::string(s))) {
        StateTransitionTable::print_invalid_char_error(s, line_number);
        exit(1);
    }
}

/**
 * Since we can't read in an EOF character,
 * we need to read in some last character to
 * properly recognize tokens at the end of a file.
 * The space ' ' character is arbitrary.
 */
void Scanner::check_for_eof()
{
    if (file.eof()) {
        next_char = ' ';
        is_eof_reached = true;
    }
}


typedef enum {
    InvalidCharacter = -10,
    InvalidTransition = -20,
    MaxIntegerLength = -30,
    MaxIdentifierLength = -40,
    MaxOperatorLength = -50
} StateTransitionTableErrors;


int StateTransitionTable::get_next_state(int current_state, std::string character)
{
    int column_index = get_column_index(character);
    return table[current_state][column_index];
}

int StateTransitionTable::get_column_index(std::string character)
{
    if (IntegerToken::is_integer(character)) {
        return 0;
    } else if (OperatorToken::is_operator(character)) {
        return 2;
    } else if (DelimiterToken::is_delimiter(character)) {
        return 3;
    } else if (character.size() > 0 && islower(character[0]) && isalpha(character[0])) {
        return 4;
    } else if (character.size() > 0 && isupper(character[0]) && isalpha(character[0])) {
        return 5;
    } else if (EndOfFileToken::is_eof(character)) {
        return 6;
    } else if (character.size() > 0 && isspace(character[0])) {
        return 7;
    }
    return -1;
}

bool StateTransitionTable::is_invalid_char(std::string character)
{
    return !is_valid_char(character);
}

bool StateTransitionTable::is_valid_char(std::string character)
{
    return (IntegerToken::is_integer(character) ||
            OperatorToken::is_operator(character) ||
            DelimiterToken::is_delimiter(character) ||
            isalpha(character[0]) ||
            EndOfFileToken::is_eof(character) ||
            isspace(character[0]));
}

bool StateTransitionTable::is_intermediate_state(int state)
{
    return !is_final_state(state);
}

bool StateTransitionTable::is_final_state(int state)
{
    return is_token_type_id(state);
}

void StateTransitionTable::print_error(int error, int line_number)
{
    std::string message = get_base_error_message();
    message.append(get_error_message(error));
    message.append(" on line ");
    std::cerr << message << line_number << std::endl;
}


void StateTransitionTable::print_invalid_char_error(std::string character, int line_number)
{
    std::string message = get_base_error_message();
    message.append(get_error_message(InvalidCharacter));
    std::cerr << message << " " << character << " on line " << line_number << std::endl;
}

std::string StateTransitionTable::get_base_error_message()
{
    return "Scanner Error: ";
}

std::string StateTransitionTable::get_error_message(int error)
{
    std::string message;
    switch (error) {
        case InvalidCharacter:
            message = "Invalid Character";
            break;
        case InvalidTransition:
            message = "Invalid transition";
            break;
        case MaxIntegerLength:
            message = "Maximum integer length exceeded";
            break;
        case MaxIdentifierLength:
            message = "Maximum identifier length exceeded";
            break;
    }
    return message;
}

Token StateTransitionTable::get_token(int state, std::string string, int line_number)
{
    switch (state) {
        case DelimiterTokenId:
            return DelimiterToken(string, line_number);
        case EndOfFileTokenId:
            return EndOfFileToken(line_number);
        case IdentifierTokenId:
            if (KeywordToken::is_keyword(string)) {
                return KeywordToken(string, line_number);
            } else {
                return IdentifierToken(string, line_number);
            }
        case IntegerTokenId:
            return IntegerToken(string, line_number);
        case OperatorTokenId:
            return OperatorToken(string, line_number);
        default:
            std::string default_token_name = get_token_type_name(DefaultTokenTypeId);
            return Token(DefaultTokenTypeId, default_token_name, line_number);
    }
}



const std::vector<std::vector<int>> StateTransitionTable::table = {
    {1, COMMENT_STATE, 10, 12, 13, InvalidTransition, EndOfFileTokenId, 0},
    {2, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {3, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {4, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {5, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {6, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {7, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {8, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {MaxIntegerLength, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {COMMENT_STATE, 0, COMMENT_STATE, COMMENT_STATE, COMMENT_STATE, COMMENT_STATE, COMMENT_STATE, COMMENT_STATE},
    {OperatorTokenId, OperatorTokenId, 11, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId},
    {MaxOperatorLength, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId},
    {DelimiterTokenId, DelimiterTokenId, DelimiterTokenId, DelimiterTokenId, DelimiterTokenId, DelimiterTokenId, DelimiterTokenId, DelimiterTokenId},
    {14, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 14, 14, IdentifierTokenId, IdentifierTokenId},
    {15, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 15, 15, IdentifierTokenId, IdentifierTokenId},
    {16, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 16, 16, IdentifierTokenId, IdentifierTokenId},
    {17, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 17, 17, IdentifierTokenId, IdentifierTokenId},
    {18, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 18, 18, IdentifierTokenId, IdentifierTokenId},
    {19, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 19, 19, IdentifierTokenId, IdentifierTokenId},
    {20, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 20, 20, IdentifierTokenId, IdentifierTokenId},
    {MaxIdentifierLength, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, MaxIdentifierLength, MaxIdentifierLength, IdentifierTokenId, IdentifierTokenId}
};
