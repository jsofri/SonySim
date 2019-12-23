//
// Created by yehonatan on 19/12/2019.
//

#include "VarCommand.h"
#include "Expression/Interpreter.h"

void VarCommand::cleanData() {
    this -> var_info = {nullptr, 0, NO_ONE};
    this->indexCounter = 0;
}

//inserting the new value in the scope's map
//if updater is client - updating the simulator
void VarCommand::updateData() {

    symbol_table.insert(make_pair(this->var_name, this->var_info));

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
    this->indexCounter++;

    if(strcmp(tokens[index].c_str(), "var") == 0) {
        setVarCommand(++index);
    }
    else {
        setVarCommand(index);
    }

    this -> updateData();

    return this->indexCounter;
}

//throw const char *
void VarCommand::setVarCommand(int index) {
    const char * token_after_name;

    this -> var_name = tokens[index];
    this -> indexCounter++;//one for the var name, second for next operator/ \n

    token_after_name = tokens[++index].c_str();

    if (strcmp(token_after_name, "\n") == 0) {
        this -> indexCounter++;
    }
    else if (strcmp(token_after_name, "=") == 0) {
        if (symbol_table.get(this -> var_name).updater == SIMULATOR) {
            throw "can't assign value to a var dependent on the simulator updates";
        }

        setValue(index+1);//index on the beginning of expression
        this -> indexCounter++;
    }
    else if(this -> isArrow(index)) {
        this -> indexCounter++;
        this -> setVarInfo(index);
    }
    else if (strcmp(token_after_name, "{") == 0) {
        return;
    }
    else if (strcmp(token_after_name, ")") == 0) {
        const char *after_curved_bracket = tokens[index + 1].c_str();
        this->indexCounter++;

        if (strcmp(after_curved_bracket, "\n") == 0) {
            this->indexCounter++;
        } else if (strcmp(after_curved_bracket, "{") == 0) {
            return;
        } else {
            throw "Invalid syntax after closing curved bracket";
        }
    }
}//end of setVarCommand()

/**
 * check if the string in the vector at the specific index is an arrow
 *
 * @param position of token in vector
 * @return boolean - 1 true / 0 false
 */
int VarCommand::isArrow(int index) {
    if (strcmp(tokens[index].c_str(), "<-") == 0) {
            return 1;
    }
    else if (strcmp(tokens[index].c_str(), "->") == 0) {
            return 1;
    }

    return 0;
}

void VarCommand::setVarInfo(int index) {
    int t, idx = index;

    //check binding direction - first char is "-" or "<"
    (tokens[index][0] == '-') ? this->var_info.updater = CLIENT : this->var_info.updater = SIMULATOR;

    //skipping "sim" in the vector
    indexCounter+=2;
    index+=2;

    this -> var_info.reference = tokens[index];

    /*
    while (tokens_array[idx++][0] != '"') {//iterate tokens and check first char is quote => start of string
        this->indexCounter++;
    }

    while (tokens_array[idx++][0] != '"') {
        this->indexCounter++;
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
    string infix;
    VarData var_data;
    float value;
    regex rgx;

    infix = tokens[index];
    rgx = interpreter -> getRegexOfTokens();

    std::regex_iterator<std::string::iterator> rit (infix.begin(), infix.end(), rgx);
    std::regex_iterator<std::string::iterator> rend;

    while (rit!=rend) {

        if (this->isVar(rit->str())) {

            if (symbol_table.find(tokens[index]) == symbol_table.end()) {
                throw "call to an unknown Variable in arithmetic expression";
            }

            var_data = symbol_table[rit->str()];

            value = var_data.value;

            interpreter->setVariable(rit->str(), value);
        }

        ++rit;
    }

    this -> indexCounter++;
}//end of setVariablesOfInterpreter()

//if it is not a number nor an operator it is a variable
//strspn returns the number of chars in str1 that's made of chars in str2
int VarCommand::isVar(string str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), "0123456789")) {
        return 0;
    }
    else if (strlen(str.c_str()) == strspn(str.c_str(), "*/-+()")) {
        return 0;
    }

    return 1;
}

string VarCommand::concatAllStrings(int index) {
    char chars[256] = {0};
    string string_of_expression;


    while (strcmp(tokens_array[index], "\n") != 0) {

        strcat(chars, tokens_array[index]);

        this -> indexCounter++;
        index++;
    }

    this -> indexCounter++;//for the \n

    string_of_expression = chars;

    return string_of_expression;
}