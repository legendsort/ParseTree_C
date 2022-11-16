#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>

#include "../node/node.h"

/**
 * Backend part of compiler responsible for:
 *   - static semantics
 *   - storage allocation
 *   - and code generation
 */

class Backend
{
    public:
        Backend(std::string base_filename);
        void traverse(Node* node);

    private:
};

#endif
