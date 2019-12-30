//
// Created by rony on 12/28/19.
//

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "CommandComment.h"

/**
 * Comment Command
 */
int CommandComment ::execute(int index) {
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (tokens[index] == "\n") {
        return execute(index + 1);
    }

    while (tokens[index] != "\n") {
        index++;
    }

    return index + 1;
}

