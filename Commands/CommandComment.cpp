/**
 * this class is a dummy command - just ignores the line.
 *
 * @authoer Rony
 * @date 12/28/19
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "CommandComment.h"

/**
 * Comment Command
 */
int CommandComment ::execute(int index) {

    while (tokens[index] != "\n") {
        index++;
    }

    return index + 1;
}

