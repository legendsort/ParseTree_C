#include "integer_token.h"

#include <string>
bool IntegerToken::is_integer(std::string character)
{
	if(character.size() == 0) return false;
	for(int i=0; i<character.size(); i++) if(!isdigit(character[i])) return false;
	return true;
}

IntegerToken::IntegerToken(std::string value, int line_number)
: Token(IntegerTokenId, value, line_number) {}
