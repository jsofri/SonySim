//
// Created by Rony Utevsky and Yehonatan Sofri on 12/19/19.
//

#include <Conditions/Condition.h>
#include <Conditions/ConditionFactory.h>
#include "CommandVar.h"


int main(int argc, char const *argv[]) {

    //testing ConditionFactory
    Condition * condition;
    ConditionFactory conditionFactory;
    string left = "4";
    string middle = ">";
    string right = "2";

    condition = conditionFactory.setCondition(left, middle, right);

    cout << condition->isTrue() <<endl;

    delete(condition);


    //end of test

    /*
    //testing CommandVar
    int index = 0;

    CommandVar varCommand;

    index += varCommand.execute(index);

    index += varCommand.execute(index);

    cout <<index<<endl;
    //end of test
    */

    return 0;
}