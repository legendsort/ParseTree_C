#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "parser.h"
#include "testTree.h"

using namespace std;
std::string get_filename(int argc, char** argv);


std::string get_basename(std::string filename)
{
    size_t last_index = filename.find_last_of('.');
    return filename.substr(0, last_index);
}

void parse(std::string filename)
{
    Parser parser(filename);
    
    Node* parse_tree = parser.parse();

    std::string basename = get_basename(filename);
	std::cout << "Parser Success\n";
    TestTree testTree;
    testTree.traverse(parse_tree);
    Node::destroy(parse_tree);
}

int main(int argc, char** argv) 
{
 
    std::string filename = get_filename(argc, argv);
    parse(filename);

    return 0;
}

std::string get_filename(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    std::string filename(argv[1]);
    return filename;
}
