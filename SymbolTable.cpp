/**
 * Symbol-Table object for the whole program.
 * each map in the list is relevant for a scope.
 * therefore, when a new scope is interpreted - it is needed to create new map in the list.
 * Similarly, delete first element when a scope is ended.
 *
 * @author Yehonatan Sofri
 * @date 23.12.19
 */

#include "SymbolTable.h"
#include "GeneralData.h"

/**
 * Constructor
 */
SymbolTable::SymbolTable() {
    unordered_map<string, VarData> first_map;

    (this -> symbol_tables).push_front(first_map);
}

/**
 * enter new value to the first map.
 *
 * @param key string - name of variable
 * @param value - VarData
 */
void SymbolTable::insert(string key, VarData value) {
    this->symbol_tables.front()[key] = value;
}

/**
 * adds new map to the list.
 */
void SymbolTable::newTable() {
    unordered_map<string, VarData> new_map;

    this->newTable(new_map);
}

/**
 * adds new table to the list.
 *
 * @param new_map to enter to beginning of list
 */
void SymbolTable::newTable(unordered_map<string, VarData> & new_map) {
    this -> symbol_tables.push_front(new_map);
}

/**
 * delete first map from the list.
 */
void SymbolTable::deleteTable() {
    this -> symbol_tables.pop_front();
}

/**
 * return value in one of the maps.
 *
 * @param str key to look for in maps
 * @return value attached to the key in the closest to the beginning
 * @throw const char * if key not found
 */
VarData SymbolTable::get(string str) {
    auto iter = this->symbol_tables.begin();
    VarData var_data;

    while (iter != this->symbol_tables.end()) {

        if ((*iter).find(str) != (*iter).end()) {
            return (*iter)[str];
        }

        iter++;
    }

    throw "Variable not found";
}
