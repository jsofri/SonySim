//
// Created by rony on 12/26/19.
//

#ifndef VARDATA_H
#define VARDATA_H

#include <string>

using namespace std;

//data that refers to a specific variable - is used in symbol_table
typedef struct VarData {
    string reference;
    float value;
    int updater;//0 = no one, 1 = client, 2 = simulator

    VarData() = default;
    VarData(float);
    VarData(string, float, int);
} VarData;

#endif //VARDATA_H
