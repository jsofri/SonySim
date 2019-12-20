/**
 * this header files contains general data for the whole program.
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef ACPROJECT_GENERALDATA_H
#define ACPROJECT_GENERALDATA_H

#include "stdio.h"
#include <unordered_map>
#include <cstring>
#include <string>
#include <vector>
#include <list>

using namespace std;

//defines for the VarData struct
#define NO_ONE 0
#define CLIENT 1
#define SIMULATOR 2

//data that is refers to a specific variable - is used in symbol_table
typedef struct VarData {
    string reference;
    float value;
    short updater;//0 = no one, 1 = client, 2 = simulator
} VarNode;

//symbol table of the program parsing process
extern unordered_map<string, VarData> symbol_table;
#endif //ACPROJECT_GENERALDATA_H
