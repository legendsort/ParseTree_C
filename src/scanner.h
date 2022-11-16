#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

class Scanner
{
    public:
        Scanner(std::string filename);
        ~Scanner();
        Token read();
    
    private:
        std::ifstream file;
        int line_number;
        char next_char;
        bool is_eof_reached;
        void check_file(std::ifstream& file, std::string filename);
        void close_file();
        void check_for_invalid_character(int state);
        void check_for_eof();
};

class StateTransitionTable
{
    public:
        static int get_next_state(int current_state, std::string character);
        static bool is_intermediate_state(int state);
        static bool is_final_state(int state);
        static bool is_error_state(int state);
        static bool is_invalid_char(std::string character);
        static bool is_valid_char(std::string character);
        static void print_error(int error, int line_number);
        static void print_invalid_char_error(std::string character, int line_number);
        static Token get_token(int state, std::string s, int line_number);

    private:
        static int get_column_index(std::string character);
        static const std::vector<std::vector<int>> table;
        static std::string get_error_message(int error);
        static std::string get_base_error_message();
};


#endif
