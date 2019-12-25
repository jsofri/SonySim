/**
 * Class for handling with variables definitions.
 * @author Yehonatan Sofri
 * @date 23.12.19
 */

#ifndef VARCOMMAND_H
#define VARCOMMAND_H

#include "GeneralData.h"
#include "Expressions/Interpreter.h"
#include "Command.h"
#include "FloatFromString.h"


class CommandVar : public Command {
public:
    void   setVarCommand(int);
    void   setValue(int);
    int    execute(int);
    int    isArrow(int);
    void   setVarInfo(int);
    void   cleanData();
    void   updateData();
    string removeQuotesFromString(int);
    CommandVar();
    ~CommandVar();
private:
    string      _var_name;
    VarData     _var_info;
    FloatFromString * _floatFromString;
};


#endif //VARCOMMAND_H
