#include "analyzer.h"

void Analyzer::_semtree_dfs(sem::Node *sem_root, exec::Node *&exec_root) {
    switch (sem_root->type) {
        case sem::Node::NOT : {
            exec_root = new exec::OperatorNOT(nullptr);
            _semtree_dfs(
                sem_root->left,
                dynamic_cast<exec::OperatorNOT *>(exec_root)->expr_
            );
            break;
        }
        case sem::Node::AND : {
            exec_root = new exec::OperatorAND(nullptr, nullptr);
            _semtree_dfs(
                sem_root->left,
                dynamic_cast<exec::OperatorAND *>(exec_root)->lhs_
            );
            _semtree_dfs(
                sem_root->right,
                dynamic_cast<exec::OperatorAND *>(exec_root)->rhs_
            );
            break;
        }
        case sem::Node::OR : {
            exec_root = new exec::OperatorOR(nullptr, nullptr);
            _semtree_dfs(
                sem_root->left,
                dynamic_cast<exec::OperatorOR *>(exec_root)->lhs_
            );
            _semtree_dfs(
                sem_root->right,
                dynamic_cast<exec::OperatorOR *>(exec_root)->rhs_
            );
            break;
        }
        case sem::Node::VARIABLE : {
            int id;
            if (var2id.contains(sem_root->name)) {
                id = var2id[sem_root->name];
            } else {
                id = var2id.size();
                var2id[sem_root->name] = id;
                res.id2var.push_back(sem_root->name);
            }
            auto &id2val = res.id2val;
            exec_root =
                new exec::Variable(id, [=] { return (*id2val)[id]; });
        }
    }
}

exec::ExecPack Analyzer::analyze(sem::Node *root) {
    _semtree_dfs(root, res.exec_root);
    res.id2val->resize(res.id2var.size());
    delete root;
    return res;
}