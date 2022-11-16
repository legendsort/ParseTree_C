#include <iostream>
#include "testTree.h"

void TestTree::traverse(Node* node)
{
    if (node == NULL) {
        return;
    }
    for(int i=0; i<2*node->level-2; i++) printf(" ");
    cout << node -> label << endl;
    for(auto child : node -> children) {
    	traverse(child);
    }
}

TestTree :: TestTree() {}
