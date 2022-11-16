#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;
#include "compiler/compiler.h"

std::string get_filename(int argc, char** argv);

int main(int argc, char** argv) 
{
 
    std::string filename = get_filename(argc, argv);
    
    Compiler compiler;
    compiler.compile(filename);

    std::cout << "OK\n";

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
