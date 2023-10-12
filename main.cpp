#include "parser/ast.h"
#include "analyze/analyzer.h"
#include "execution/executor.h"

#include "parser/parser_def.h"

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <format>

extern int yyparse();

std::string MSP(const std::vector<std::string> &id2var, int varcnt, const std::vector<char> &truth_table) {
    std::string msp;
    for (int i = 0; i < (1 << varcnt); i += 1) {
        if (truth_table[i] == true) {
            continue;
        }
        if (!msp.empty()) {
            msp += " & ";
        }
        msp += '(';
        for (int id = 0; id < varcnt; id += 1) {
            if (id != 0) {
                msp += " | ";
            }
            if ((i >> id) & 1) {
                msp+= '!';
            }
            msp += id2var[id];
        }
        msp += ')';
    }
    return msp;
}

std::string MPS(const std::vector<std::string> &id2var, int varcnt, const std::vector<char> &truth_table) {
    std::string mps;
    for (int i = 0; i < (1 << varcnt); i += 1) {
        if (truth_table[i] == false) {
            continue;
        }
        if (!mps.empty()) {
            mps += " | ";
        }
        mps += '(';
        for (int id = 0; id < varcnt; id += 1) {
            if (id != 0) {
                mps += " & ";
            }
            if (!((i >> id) & 1)) {
                mps+= '!';
            }
            mps += id2var[id];
        }
        mps += ')';
    }
    return mps;
}


int main() {
    std::string str;
    std::getline(std::cin, str);
    YY_BUFFER_STATE buf = yy_scan_string(str.c_str());

    yyparse();

    Analyzer analyzer;
    auto exec_pack = analyzer.analyze(sem::parse_tree);

    int varcnt = exec_pack.id2var.size();

    std::cout << '\t' << "\x1b[1m";
    for (int id = 0; id < varcnt; id += 1) {
        std::cout << exec_pack.id2var[id] << '\t';
    }
    std::cout << "Ans" << '\n' << "\x1b[0m";

    std::vector<char> truth_table(1 << varcnt);

    for (uint64_t i = 0; i < (1 << varcnt); i += 1) {
        std::cout << i << '\t' << "\x1b[2m";
        for (int k = 0; k < varcnt; k += 1) {
            (*exec_pack.id2val)[k] = ((i >> k) & 1);
            std::cout << ((*exec_pack.id2val)[k] ? 'T' : 'F') << '\t';
        }
        auto ans = exec_pack.exec_root->calc();
        std::cout << (ans ? 'T' : 'F') << '\n' << "\x1b[0m";
        truth_table[i] = ans;
    }

    std::cout << std::endl;

    std::cout << std::format("\x1b[1m主合取范式: \x1b[0m {}\n", MSP(exec_pack.id2var, varcnt, truth_table));
    std::cout << std::format("\x1b[1m主析取范式: \x1b[0m {}\n", MPS(exec_pack.id2var, varcnt, truth_table));
}