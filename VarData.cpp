//
// Created by rony on 12/27/19.
//

#include "GeneralData.h"
#include "VarData.h"

using namespace std;

VarData :: VarData(string reference, float value, int update): reference(reference), value(value), updater(updater) {}

VarData :: VarData(float value): value(value) {}