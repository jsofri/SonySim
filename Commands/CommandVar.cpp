/**
 * Class for handling with variables definitions.
 * @author Yehonatan Sofri
 * @date 23.12.19
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "CommandVar.h"

/**
 * Ctor.
 */
CommandVar::CommandVar() {
    this -> _floatFromString = new FloatFromString();
}

/**
 * reset all data of object
 */
void CommandVar::cleanData() {
    this -> _var_info = {"", 0, NO_ONE};
    this->indexCounter = 0;
}

/**
 * inserting the new value in the scope's map
 * if updater is client - updating the simulator
 * @param shouldEnqueue if the var should be enqueued to the simulator queue
 */
void CommandVar::updateData(bool shouldEnqueue) {

    symbol_table.insert(this->_var_name, this->_var_info);

    if (this->_var_info.updater == CLIENT && shouldEnqueue) {
        updateSimulatorQueue.enqueue(this -> _var_info);
        //cout << "enqueued: " << _var_name << " " << _var_info.value << "| ";
        //cout << "queue status: " << !updateSimulatorQueue.isEmpty() << endl;
    }
}

/**
 * reset the object data, and set/ update a var in the map.
 *
 * @param index in vector of tokens
 * @return number of cells in tokens_array to go ahead
 */
int CommandVar::execute(int index) {

    this->cleanData();
    this->indexCounter = index;

    bool shouldEnqueue;

    if (tokens[index] == "var") {
        this -> indexCounter++;
        shouldEnqueue = setVarCommand(++index);
    }
    else {
        shouldEnqueue = setVarCommand(index);
    }

    this->updateData(shouldEnqueue);

    return this -> indexCounter;
}

/**
 * handle a var creation/ update command, depending on the sequence of strings in vector.
 *
 * @param index in vector of tokens
 * @throw const char * in case of invalid input
 * @return true if should enqueue the var to the simulator queue
 */
bool CommandVar::setVarCommand(int index) {//x =...\ x <- ...
    string token_after_name;

    this -> _var_name = tokens[index];//x
    this -> indexCounter++;//= / -> / \n / {

    token_after_name = tokens[++index]; //= / -> / \n / {

    if (token_after_name == "\n") {
        this -> indexCounter++;
        return false;
    }
    else if (token_after_name == "=") {
        bool boolean;
        if (!symbol_table.exists(_var_name)) {
            FloatFromString floatFromStringExpression;

            this->_var_info.updater = NO_ONE;

            this -> _var_info.value = floatFromStringExpression.calculateString(tokens[index+1]);

            symbol_table.insert(_var_name, this ->_var_info);
            this -> indexCounter += 3;

            boolean = false;
        } else {

            this -> indexCounter++;//expression / value

            this->_var_info.updater = symbol_table.get(_var_name).updater;
            setValue(index+1);//index in the beginning of expression

            boolean = true;
        }

        return boolean;
    }
    else if(this -> isArrow(index)) {
        this -> setVarInfo(index);
        return false;
    }
    else if (token_after_name == "{") {
        return false;
    }
    else {
        throw "Invalid input";
    }
}//end of setVarCommand()

/**
 * check if the string in the vector at the specific index is an arrow.
 * arrow is "->" or "<-"
 *
 * @test 12.26.19 by YS
 * @param position of token in vector
 * @return boolean - 1 true / 0 false
 */
int CommandVar::isArrow(int index) {
    if ((tokens[index] == "<-")  || (tokens[index] == "->")) {
            return 1;
    }

    return 0;
}

/**
 * creating a Var - setting reference and updater by direction of arrow.
 *
 * @test in 26.12.19 by YS
 * @param index in vector, pointing to arrow
 */
void CommandVar::setVarInfo(int index) {

    //check binding direction - first char is "-" or "<"
    this->_var_info.updater = (tokens[index][0] == '-') ? CLIENT : SIMULATOR;

    this -> _var_info.reference = this -> removeQuotesFromString(index + 2);//skiping arrow, "sim"

    if (this -> _var_info.updater == SIMULATOR) {
        int placeInCSV = xmlRefToIndexMap[this -> _var_info.reference];

        xmlIndexToVarMap[placeInCSV].push_back(this ->_var_name);
    }

    //skipping arrow, "sim", reference, "\n"
    this -> indexCounter += 4;
}

/**
 * get a string and remove substring, without the first and last characters.
 * used for removing quotes.
 *
 * @test in 12.26.19 by YS
 * @param index in the tokens vector
 * @return string in tokens[index] without quotes
 */
string CommandVar::removeQuotesFromString(int index) {
    string str = tokens[index];
    int n = strlen(str.c_str());

    str = str.substr(1, n - 2);

    return str;
}

/**
 * calculate the value in the string that index points to.
 *
 * @param index in vector of tokens
 */
void CommandVar::setValue(int index) {
    FloatFromString floatFromStringExpression;

    this -> _var_info.value = floatFromStringExpression.calculateString(tokens[index]);
    this -> _var_info.reference = symbol_table.get(this -> _var_name).reference;

    this->indexCounter+=2;//skipping expression and "\n"
}

/**
 * Dtor.
 */
CommandVar::~CommandVar() {
    delete(this->_floatFromString);
}
