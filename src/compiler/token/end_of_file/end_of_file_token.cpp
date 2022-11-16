#include <stdio.h>
#include "end_of_file_token.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>

 bool EndOfFileToken::is_eof(std::string character)
 {
     return character[0] == EOF;
 }

EndOfFileToken::EndOfFileToken(int line_number)
: Token(EndOfFileTokenId, "EOF", line_number) {}
