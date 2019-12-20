//
// Created by yehonatan on 19/12/2019.
//

#include "SymbolTable.h"

using namespace std;

//CTOR - set one map in the list_of_maps
SymbolTable::SymbolTable() {
    this -> enterNewSymbolTable();
}

void SymbolTable::deleteSymbolTable() {
    this -> list_of_maps.pop_front();
}

//iterate on the maps in the list_of_maps, from first to last, and look for key in each map
//if nothing is found - doesn't return anything
VarData SymbolTable::get(string key) {
    std::list<unordered_map<string, VarData>>::iterator iter;
    unordered_map<string, VarData> tmp_map;
    unordered_map<string, VarData>::iterator value;

    for (iter = this -> list_of_maps.begin(); iter != this -> list_of_maps.end(); ++iter) {
        tmp_map = *iter;
        value = tmp_map.find(key);

        if (value != tmp_map.end()) {
            return value -> second;
        }
    }
}

//entering key value pair to first map
void SymbolTable::insert(string key, VarData value) {
    std::list<unordered_map<string, VarData>>::iterator first_map_iterator;

    first_map_iterator = this -> list_of_maps.begin();
    (*first_map_iterator)[key] = value;

}

void SymbolTable::enterNewSymbolTable() {
    unordered_map<string, VarData> new_map;

    this -> list_of_maps.push_front(new_map);
}
