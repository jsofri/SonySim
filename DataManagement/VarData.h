/**
 * VarData class is essentially a struct that hold 3 things:
 * (1) reference to simulator (a path, e.g. `engines/engine/rpm`) 
 * (2) the value (floating point number)
 * (3) the updater of the variable: Simulator / Client / No one.
 * 
 * Structs like this are held in the Symbol Table.
 * 
 * @date 12/21/19
 * @author Rony Utevsky
 **/

#ifndef VARDATA_H
#define VARDATA_H

#include <string>
using namespace std;

typedef struct VarData {
    string reference;
    float value;
    int updater; //0 = no one, 1 = client, 2 = simulator

    VarData() = default;
    VarData(float);
    VarData(string, float, int);
} VarData;

#endif //VARDATA_H
