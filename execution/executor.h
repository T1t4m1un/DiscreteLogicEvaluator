#pragma once

#include <functional>
#include <vector>
#include <string>

#include <boost/utility.hpp>

namespace exec {

struct Node : boost::noncopyable {
    virtual bool calc() = 0;
    virtual ~Node() {};
};

struct Variable : Node {
    int id_;
    std::function<bool()> get_val_;

    explicit Variable(int id, std::function<bool()> get_val)
        : id_(id), get_val_(std::move(get_val))
    {}

    virtual bool calc() final { return get_val_(); }

    ~Variable() {}
};

struct OperatorNOT : Node {
    Node *expr_;

    explicit OperatorNOT(Node *expr)
        : expr_(expr)
    {}

    virtual bool calc() final { return !expr_->calc(); } 

    virtual ~OperatorNOT() { delete expr_; }
};

struct OperatorAND : Node {
    Node *lhs_, *rhs_;

    explicit OperatorAND(Node *lhs, Node *rhs)
        : lhs_(lhs), rhs_(rhs)
    {}

    virtual bool calc() final { return (lhs_->calc() && rhs_->calc()); }

    virtual ~OperatorAND() { delete lhs_, rhs_; }
};

struct OperatorOR : Node {
    Node *lhs_, *rhs_;

    explicit OperatorOR(Node *lhs, Node *rhs)
        : lhs_(lhs), rhs_(rhs)
    {}

    virtual bool calc() final { return (lhs_->calc() || rhs_->calc()); }

    virtual ~OperatorOR() { delete lhs_, rhs_; }
};

struct ExecPack : boost::noncopyable {
    Node *exec_root;
    std::vector<char> *id2val;
    std::vector<std::string> id2var;

    explicit ExecPack() {
        exec_root = nullptr;
        id2val = new std::vector<char>();
    }

    ExecPack(ExecPack &other) {
        exec_root = other.exec_root;
        other.exec_root = nullptr;

        id2val = other.id2val;
        other.id2val = nullptr;

        id2var = std::move(other.id2var);
    }

    ~ExecPack() { delete exec_root, id2val; }
};

}