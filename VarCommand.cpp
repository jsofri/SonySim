//
// Created by yehonatan on 19/12/2019.
//

#include "VarCommand.h"
#include "Expressions/Interpreter.h"

void VarCommand::cleanData() {
    this -> var_info = {nullptr, 0, NO_ONE};
    this->index_counter = 0;
}

//inserting the new value in the scope's map
//if updater is client - updating the simulator
void VarCommand::updateData() {
    symbol_table.insert(this->var_name, this->var_info);

    if (this->var_info.updater == CLIENT) {
        cout <<"now i should update the simulator: ";
        cout << this ->var_name << this ->var_info.value<< endl;
        //updateSimulator(this -> var_info.reference, this -> var_info.value);
    }
}

//get index in tokens_array of tokens
//reset the object data, and set/ update a var in the map
//returns number of cells in tokens_array to go ahead
int VarCommand::execute(int index) {
    this->cleanData();
    this->index_counter++;

    if(strcmp(tokens_array[index], "var") == 0) {
        setVarCommand(++index);
    }
    else {
        setVarCommand(index);
    }

    this -> updateData();

    return this->index_counter;
}

//throw const char *
void VarCommand::setVarCommand(int index) {
    const char * token_after_name;

    this -> var_name = tokens_array[index];
    this -> index_counter++;//one for the var name, second for next operator/ \n

    token_after_name = tokens_array[++index];

    if (strcmp(token_after_name, "\n") == 0) {
        this -> index_counter++;
    }
    else if (strcmp(token_after_name, "=") == 0) {
        if (symbol_table.get(this -> var_name).updater == SIMULATOR) {
            throw "can't assign value to a var dependent on the simulator updates";
        }

        setValue(index+1);//index on the beginning of expression
        this -> index_counter++;
    }
    else if(this -> isArrow(index)) {
        this -> index_counter+=2;   ///////////////////////////////?????????////////////////////depends
        this -> setVarInfo(index);///////////////////////////////?????????////////////////////depends
    }
    else if (strcmp(token_after_name, "{") == 0) {
        return;
    }
    else if (strcmp(token_after_name, ")") == 0) {
        const char *after_curved_bracket = tokens_array[index + 1];
        this->index_counter++;

        if (strcmp(after_curved_bracket, "\n") == 0) {
            this->index_counter++;
        } else if (strcmp(after_curved_bracket, "{") == 0) {
            return;
        } else {
            throw "Invalid syntax after closing curved bracket";
        }
    }
}//end of setVarCommand()

//check if 2 next tokens in tokens_array form an arrow // "-"+">" or "<"+"-"
int VarCommand::isArrow(int index) {
    if (strcmp(tokens_array[index], "<") == 0) {
        if (strcmp(tokens_array[index + 1], "-") == 0) {
            return 1;
        }
    }
    else if (strcmp(tokens_array[index], "-") == 0) {
        if (strcmp(tokens_array[index + 1], ">")) {
            return 1;
        }
    }

    return 0;
}

void VarCommand::setVarInfo(int index) {////////////////////////////////????????????//////////////
    int t, idx = index;
    //char buffer[512] = {0};

    //check binding direction - 2 first tokens are guaranteed to build an arrow
    (tokens_array[index][0] == '-') ? this->var_info.updater = CLIENT : this->var_info.updater = SIMULATOR;

    /*
    while (tokens_array[idx++][0] != '"') {//iterate tokens and check first char is quote => start of string
        this->index_counter++;
    }

    while (tokens_array[idx++][0] != '"') {
        this->index_counter++;
        t = 0;
    }
     */
    //this -> var_info.reference = string_of_reference;
}

void VarCommand::setValue(int index) {
    Interpreter* interpreter = new Interpreter();
    Expression* expression = nullptr;
    string expression_string;

    try {

        this -> setVariablesOfInterpreter(index, interpreter);

        expression_string = this->concatAllStrings(index);
        expression = interpreter->interpret(expression_string);

        this->var_info.value = expression->calculate();
        delete expression;
        delete interpreter;
    } catch (const char* e) {
        if (expression != nullptr) {
            delete expression;
        }
        if (interpreter != nullptr) {
            delete interpreter;
        }
    }
}

void VarCommand::setVariablesOfInterpreter(int index, Interpreter *& interpreter) {
    const char * variable_and_value = nullptr;
    VarData var_data;
    float value;


    while (strcmp(tokens_array[index], "\n") != 0) {

        if (this -> isVar(index)) {
            var_data = symbol_table.get(tokens_array[index]);

            value = var_data.value;

            interpreter -> setVariable(tokens_array[index], value);
        }

        index++;
    }
}

//if it is not a number nor an operator it is a variable
//strspn returns the number of chars in str1 that's made of chars in str2
int VarCommand::isVar(int index) {
    if (strlen(tokens_array[index]) == strspn(tokens_array[index], "0123456789")) {
        return 0;
    }
    else if (strlen(tokens_array[index]) == strspn(tokens_array[index], "*/-+()")) {
        return 0;
    }

    return 1;
}

string VarCommand::concatAllStrings(int index) {
    char chars[256] = {0};
    string string_of_expression;


    while (strcmp(tokens_array[index], "\n") != 0) {

        strcat(chars, tokens_array[index]);

        this -> index_counter++;
        index++;
    }

    this -> index_counter++;//for the \n

    string_of_expression = chars;

    return string_of_expression;
}