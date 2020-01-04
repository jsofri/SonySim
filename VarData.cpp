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

#include "GeneralData.h"
#include "VarData.h"

/**
 * Constructor
 *
 * @param referece the reference
 * @param value the value
 * @param updater the updater
 **/
VarData :: VarData(string ref, float val, int updater_id): reference(ref), value(val), updater(updater_id) {}

/**
 * Constructor
 *
 * @param value the value
 **/
VarData :: VarData(float val): value(val) {}
