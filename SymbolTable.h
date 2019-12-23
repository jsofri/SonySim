//
// Created by yehonatan on 23/12/2019.
//

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "GeneralData.h"

class SymbolTable {
public:
    void newTable();
    void newTable(unordered_map<string, VarData> &);
    void deleteTable();
    VarData get(string);
    void insert(string, VarData);
    SymbolTable();
    ~SymbolTable() = default;
private:
    list<unordered_map<string, VarData>> symbol_tables;
};


#endif //SYMBOLTABLE_H
