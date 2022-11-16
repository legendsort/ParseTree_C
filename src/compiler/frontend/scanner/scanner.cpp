#include <fstream>
#include <iostream>
#include <string>

#include "scanner.h"
#include "state_transition_table/state_transition_table.h"
#include <bits/stdc++.h>

using namespace std;


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
        std::cerr << "Error: Cannot open file '" << filename << "'.\n";
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
	cerr<<"new char: "<<(int)next_char<<' '<<next_char<<' '<<state<<endl;
    int next_state = StateTransitionTable::get_next_state(state, s);
    std::string string = "";
    

    do {
    	s = "";
		s += next_char;
    	cerr<<"new char: "<<(int)next_char<<' '<<next_char<<' '<<state<<endl;
        check_for_eof();
        
        check_for_invalid_character(state);

        next_state = StateTransitionTable::get_next_state(state, s);
		cerr<<"-------->"<<string.size()<<' '<<state<<' '<<next_state<<' ' <<(int)next_char<<endl;
        check_for_table_error(next_state);
        if (StateTransitionTable::is_final_state(next_state)) {
        	cerr<<"Token: "<<string<<endl;
            return StateTransitionTable::get_token(next_state, string, line_number);
        } else {
            state = next_state;
            if (!isspace(next_char)) {
//				cerr<<"string added: "<<' '<<state<<endl;
                string += next_char;
            }
            
        }
//        cerr<<"======>"<<string.size()<<' '<<state<<' '<<next_state<<' ' <<(int)next_char<<endl;
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

void Scanner::check_for_table_error(int state)
{
    if (is_table_error(state)) {
        StateTransitionTable::print_error(state, line_number);
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
