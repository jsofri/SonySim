/**
 * Symbol-Table object for the whole program.
 * each map in the list is relevant for a scope.
 * therefore, when a new scope is interpreted - it is needed to create new map in the list.
 * Similarly, delete first element when a scope is ended.
 * Class is used by multiple threads, therefore mutex protection in methods.
 *
 * @author Yehonatan Sofri
 * @date 23.12.19
 */

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
    pthread_mutex_t object_locker;
};


#endif //SYMBOLTABLE_H
