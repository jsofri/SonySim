//
// Created by Rony Utevsky and Yehonatan Sofri on 12/19/19.
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

using namespace std;

class Parser {
    public:

    /**
     * Parse the tokens and execute commands
     * @param start the index to begin parsing
     * @param end the index to end parsing
     * @param tokenArr the vector to use
     */
    void parse(int, int, vector<string> &);

    /**
     * Parse the tokens and execute commands.
     * @param tokenArr token array
     */
    void parse(vector<string>);

    /**
     * Parse the tokens and execute commands
     * @param start the index to begin parsing
     * @param end the index to end parsing
     */
    void parse(int, int);

    /**
     * Parse the tokens and execute commands
     * @param start the index to begin parsing
     */
    void parse(int);

    /**
     * Parse the tokens and execute commands.
     * Default index is 0.
     */
    void parse();

    /**
     * parse the command type (var, update, func, while, if etc.)
     * @param tokensRow a row of tokens
     * @return the command type
     */
    string parseCommandType(vector<string> &, int);

    /**
     * Check if a while loop should run
     * @param row the token row
     * @return true if a while loop should run
     */
    bool isWhile(vector<string> &);

    /**
    * Check if an IF condition should run
    * @param row the token row
    * @return true if an IF condition should run
    */
    bool isIF(vector<string> &);

    /**
    * Check if a Print command should run
    * @param row the token row
    * @return true if a Print command should run
    */
    bool isPrint(vector<string> &);

    /**
    * Check if a Sleep command should run
    * @param row the token row
    * @return true if a Sleep command should run
    */
    bool isSleep(vector<string> &);

    /**
    * Check if an `Open Data Server` command should run
    * @param row the token row
    * @return true if an `Open Data Server` command should run
    */
    bool isOpenServer(vector<string> &);

    /**
    * Check if a `Connect Control Client` command should run
    * @param row the token row
    * @return true if a `Connect Control Client` command should run
    */
    bool isConnect(vector<string> &);

    /**
     * Check if a variable command should run
     * @param row the token row
     * @return true if a variable command should run
     */
    bool isVar(vector<string> &);

    /**
     * Check if a function definition command should run
     * @param row the token row
     * @return true if a function definition command should run
     */
    bool isFuncDef(vector<string> &, int ) ;

    /**
     * Check if a function call command should run
     * @param row the token row
     * @return true if a function call command should run
     */
    bool isFuncCall(vector<string> &);

    /**
    * Check if an Update command should run
    * @param row the token row
    * @return true if an Update command should run
    */
    bool isUpdate(vector<string> &);

    /**
    * Check if a the line is commented and should be ingored
    * @param row the token row
    * @return true if the line is a comment and should be ingored
    */
    bool isComment(vector<string> &);

};

#endif //PARSER_H
