/**
 * Abstract class for all command objects.
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef ACPROJECT_COMMAND_H
#define ACPROJECT_COMMAND_H

#include "GeneralData.h"

class Command {
public:

    /**
     * interpret and execute, depending on the strings sequence in the vector.
     *
     * @param vector<string> &
     * @param int index - index in the vector
     * @return int - index counter in the vector
     */
    virtual int execute(int, vector<string> &) = 0;
protected:

    //count number of strings that were handled in the vector
    int index_counter = 0;
};
#endif //ACPROJECT_COMMAND_H
