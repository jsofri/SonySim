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

#include "SymbolTable.h"

/**
 * Constructor
 */
SymbolTable::SymbolTable() {
    unordered_map<string, VarData> first_map;

    (this -> _symbol_tables).push_front(first_map);
}

/**
 * enter new value to the first map.
 *
 * @param key string - name of variable
 * @param value - VarData
 */
void SymbolTable::insert(string &key, VarData & value) {
    lock_guard<mutex> lock(_locker);

    this->_symbol_tables.front()[key] = value;
}

/**
 * adds new map to the list.
 */
void SymbolTable::newTable() {
    lock_guard<mutex> lock(_locker);

    unordered_map<string, VarData> new_map;

    this -> _symbol_tables.push_front(new_map);
}

/**
 * adds new table to the list.
 *
 * @param new_map to enter to beginning of list
 */
void SymbolTable::newTable(unordered_map<string, VarData> & new_map) {
    lock_guard<mutex> lock(_locker);

    this -> _symbol_tables.push_front(new_map);
}

/**
 * delete first map from the list.
 */
void SymbolTable::deleteTable() {
    lock_guard<mutex> lock(_locker);

    this -> _symbol_tables.pop_front();
}

/**
 * return value in one of the maps.
 *
 * @param str key to look for in maps
 * @return value attached to the key in the closest to the beginning
 * @throw const char * if key not found
 */
VarData SymbolTable::get(string str) {
    lock_guard<mutex> lock(_locker);
    auto                        iter = this->_symbol_tables.begin();

    while (iter != this -> _symbol_tables.end()) {

        if ((*iter).find(str) != (*iter).end()) {
            return (*iter)[str];
        }

        iter++;
    }

    throw "Variable not found";
}

/**
 * check if a key exist in the symbol table.
 *
 * @param str - key to look for in symbol table
 * @return boolean
 */
bool SymbolTable::exists(string & str) {
    lock_guard<mutex> lock(_locker);
    auto                        iter = this->_symbol_tables.begin();

    while (iter != this -> _symbol_tables.end()) {
        if ((*iter).find(str) != (*iter).end()) {
            return true;
        }

        iter++;
    }

    return false;
}
