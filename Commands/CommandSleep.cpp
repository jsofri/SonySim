/**
 * Class for handling with sleep command.
 *
 * @author Yehonatan Sofri
 * @date 12.25.19
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
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
