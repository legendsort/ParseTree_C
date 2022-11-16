#include "compiler.h"

#include "frontend/frontend.h"


void Compiler::compile(std::string filename)
{
    Parser parser(filename);
    Node* parse_tree = parser.parse();

    std::string basename = get_basename(filename);
    
    Node::destroy(parse_tree);
}

std::string Compiler::get_basename(std::string filename)
{
    size_t last_index = filename.find_last_of('.');
    return filename.substr(0, last_index);
}
