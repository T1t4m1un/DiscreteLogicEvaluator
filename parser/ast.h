#pragma once

#include <string>

// sementic AST node types

namespace sem {

struct Node {
    enum NodeType { VARIABLE, NOT, AND, OR };

    NodeType type;
    std::string name;
    Node* left;
    Node* right;

    Node(NodeType t, std::string n = "", Node* l = nullptr, Node* r = nullptr)
        : type(t), name(n), left(l), right(r) {}

    ~Node() { delete left, right; }
};

extern Node *parse_tree;

}

#define YYSTYPE sem::Node*
