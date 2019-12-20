//
// Created by yehonatan on 19/12/2019.
//

#ifndef ACPROJECT_SYMBOLTABLE_H
#define ACPROJECT_SYMBOLTABLE_H


#include "GeneralData.h"
#include <list>

/*
 * This Object make it possible to have a few symbol tables in program.
 * each map is used for a scope, so once a scope is created, new map should be pushed in front
 * similarly, if a scope is terminated, a map should be popped from front
 * the order of the list_of_maps is that the outer scope is last and "innest" scope is first
 */

class SymbolTable {
public:
    SymbolTable();
    void insert(string, VarData);
    VarData get(string);
    void enterNewSymbolTable();
    void deleteSymbolTable();
private:
    list <unordered_map<string, VarData>> list_of_maps;
};

extern SymbolTable symbol_table;
#endif //ACPROJECT_SYMBOLTABLE_H
