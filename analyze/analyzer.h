#pragma once

#include <tuple>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include <boost/utility.hpp>

#include "parser/ast.h"
#include "execution/executor.h"

class Analyzer {
    std::map<std::string, int> var2id;
    exec::ExecPack res;

    void _semtree_dfs(sem::Node *sem_root, exec::Node *&exec_root);
public:
    exec::ExecPack analyze(sem::Node *root);
};