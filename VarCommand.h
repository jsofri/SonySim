//
// Created by yehonatan on 19/12/2019.
//

#ifndef ACPROJECT_VARCOMMAND_H
#define ACPROJECT_VARCOMMAND_H

#include "GeneralData.h"
#include "Expression/Interpreter.h"
#include "Command.h"


class VarCommand : public Command {
public:
    void setVarCommand(int);
    void setValue(int);
    int execute(int);
    int isArrow(int);
    void setVarInfo(int);
    void setVariablesOfInterpreter(int, Interpreter*&);
    int isVar(string);
    string concatAllStrings(int);
    void cleanData();
    void updateData();
    VarCommand();
    ~VarCommand() = default;
private:
    string var_name;
    VarData     var_info;
};


#endif //ACPROJECT_VARCOMMAND_H
