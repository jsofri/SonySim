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
    this ->_locker = PTHREAD_MUTEX_INITIALIZER;
}

/**
 * enter new value to the first map.
 *
 * @param key string - name of variable
 * @param value - VarData
 */
void SymbolTable::insert(string key, VarData value) {
    pthread_mutex_lock(&(this->_locker));

    this->_symbol_tables.front()[key] = value;

    pthread_mutex_unlock(&(this->_locker));
}

/**
 * adds new map to the list.
 */
void SymbolTable::newTable() {
    pthread_mutex_lock(&(this->_locker));

    unordered_map<string, VarData> new_map;

    this -> _symbol_tables.push_front(new_map);

    pthread_mutex_unlock(&(this->_locker));
}

/**
 * adds new table to the list.
 *
 * @param new_map to enter to beginning of list
 */
void SymbolTable::newTable(unordered_map<string, VarData> & new_map) {
    pthread_mutex_lock(&(this->_locker));

    this -> _symbol_tables.push_front(new_map);

    pthread_mutex_unlock(&(this->_locker));
}

/**
 * delete first map from the list.
 */
void SymbolTable::deleteTable() {
    pthread_mutex_lock(&(this->_locker));

    this -> _symbol_tables.pop_front();

    pthread_mutex_unlock(&(this->_locker));
}

/**
 * return value in one of the maps.
 *
 * @param str key to look for in maps
 * @return value attached to the key in the closest to the beginning
 * @throw const char * if key not found
 */
VarData SymbolTable::get(string str) {
    pthread_mutex_lock(&(this->_locker));
    auto                        iter = this->_symbol_tables.begin();
    VarData                     var_data;

    while (iter != this->_symbol_tables.end()) {

        if ((*iter).find(str) != (*iter).end()) {
            VarData var_data = (*iter)[str];
            pthread_mutex_unlock(&(this->_locker));
            return var_data;
        }

        iter++;
    }

    pthread_mutex_unlock(&(this->_locker));
    throw "Variable not found";
}

SymbolTable::~SymbolTable() {
    pthread_mutex_destroy(&(this-> _locker));
}
