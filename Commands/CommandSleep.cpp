/**
 * Class for handling with sleep command.
 * @author Yehonatan Sofri
 * @date 12.25.19
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "CommandSleep.h"

/**
 * Constructor
 */
CommandSleep::CommandSleep() {
    this -> _floatFromString = new FloatFromString();
}

/**
 * make this thread sleep for number of milliseconds in tokens[index[
 * @param index in vector of string (tokens)
 * @return indexCounter value - in this command is const
 */
int CommandSleep::execute(int index) {
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (tokens[index] == "\n") {
        return execute(index + 1);
    }

    float value = this ->_floatFromString->calculateString(tokens[++index]);
    chrono::milliseconds dura((int) value);

    this_thread::sleep_for(dura);

    return index + 2;
}

/**
 * Destructor.
 */
CommandSleep::~CommandSleep() {
    delete(this -> _floatFromString);
}