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

#include "VarData.h"

class SymbolTable {
public:
    /**
     * adds new map to the list.
     */
    void    newTable();
    
    /**
     * adds new table to the list.
     *
     * @param new_map to enter to beginning of list
     */
    void    newTable(unordered_map<string, VarData> &);
    
    /**
     * delete first map from the list, i.e. delete the innermost scope's list
     */
    void    deleteTable();
    
    /**
     * check if a key exist in the symbol table.
     *
     * @param str - key to look for in symbol table
     * @return boolean
     */
    bool    exists(string &);
    
    /**
     * return value in one of the maps.
     *
     * @param str key to look for in maps
     * @return value attached to the key in the closest to the beginning
     * @throw char * if key not found
     */
    VarData& get(string);
    
    /**
     * enter new value to the first map.
     *
     * @param key string - name of variable
     * @param value - VarData
     */
    void    insert(string &, VarData &);
    
    /**
     * update field "value" in the var data node that's represented by key.
     * @param key string key in symbolTable
     * @param value in varData of the specific key
     */
    void    update(string &, float);
    
    /**
     * Constructor
     */
    SymbolTable();
    
    /**
     * Destructor
     */
    ~SymbolTable() = default;
    
private:
    // a list that holds all the maps (each map represents a scope in the code - currently maximum 2 maps)
    list<unordered_map<string, VarData>> _symbol_tables;
    mutex _locker;
};


#endif //SYMBOLTABLE_H
