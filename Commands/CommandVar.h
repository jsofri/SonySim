/**
 * Class for handling with variables definitions.
 * @author Yehonatan Sofri
 * @date 23.12.19
 */

#ifndef VARCOMMAND_H
#define VARCOMMAND_H

#include "../DataManagement/VarData.h"
#include "../DataManagement/FloatFromString.h"
#include "Command.h"


class CommandVar : public Command {
public:
    bool   setVarCommand(int);
    void   setValue(int);
    int    execute(int);
    int    isArrow(int);
    void   setVarInfo(int);
    void   cleanData();
    void   updateData(bool);
    string removeQuotesFromString(int);
    CommandVar();
    ~CommandVar();
private:
    string            _var_name;
    VarData           _var_info;
    FloatFromString * _floatFromString;
};


#endif //VARCOMMAND_H
