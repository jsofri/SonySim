/**
 * Class for handling with sleep command.
 * @author Yehonatan Sofri
 * @date 12.25.19
 */

#include "CommandSleep.h"

/**
 * Constructor
 */
CommandSleep::CommandSleep() {
    this -> floatFromString = new FloatFromString();
}

/**
 * make this thread sleep for number of milliseconds in tokens[index[
 * @param index in vector of string (tokens)
 * @return indexCounter value - in this command is const
 */
int CommandSleep::execute(int index) {
    float value = this ->floatFromString->calculateString(tokens[index]);
    chrono::milliseconds dura((int) value);

    this_thread::sleep_for(dura);

    return 2?3;////////////////
    what number?
}

/**
 * Destructor.
 */
CommandSleep::~CommandSleep() {
    delete(this -> floatFromString);
}