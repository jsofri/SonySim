/**
 * Abstract class for all command objects.
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef COMMAND_H
#define COMMAND_H

/**
 * Base abstract class of Command object
 */
class Command {
public:

    /**
     * interpret and execute
     *
     * @param vector<string> & the tokens from lexer
     * @param int index - index in the vector
     * @return int - index counter in the vector
     */
    virtual int execute(int) = 0;
    virtual ~Command() = default;
protected:

    //count number of strings that were handled in the vector
    int indexCounter = 0;
};

#endif //COMMAND_H
