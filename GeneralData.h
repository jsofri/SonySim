//
// Created by yehonatan on 19/12/2019.
//

#ifndef ACPROJECT_GENERALDATA_H
#define ACPROJECT_GENERALDATA_H

#include "stdio.h"
#include <unordered_map>
#include <cstring>
#include <string>
#include <vector>


#define NO_ONE 0
#define CLIENT 1
#define SIMULATOR 2

using namespace std;

typedef struct VarData {
    string reference;
    float value;
    short updater;//0 = no one, 1 = client, 2 = simulator
} VarNode;

extern vector<const char *> tokens_array;
#endif //ACPROJECT_GENERALDATA_H
