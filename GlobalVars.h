//
// Created by rony on 12/28/19.
//

#ifdef A_H_
    #define EXTERN
#else
    #define EXTERN extern
#endif


// the lexer array of tokens
EXTERN vector<string> tokens;

// map that stores:
// (1) function name
// (2) start index of definition in the lexer token array
// (3) map parameters names and values
EXTERN unordered_map<string, pair<int, vector<string>>> funcMap;

// map of all commands (initialized in main.cpp)
EXTERN unordered_map<string, Command*> cmdMap;

// key: index in XML, value: variable name in symbol table
// Note: this map stores only var names that are SIMULATOR-wrapped (i.e. `<-` binding)
EXTERN unordered_map<int, vector<string>> xmlIndexToVarMap;

// key: simulator reference, value: index in XML (initialized in main.cpp)
EXTERN unordered_map<string, int> xmlRefToIndexMap;

// symbol table of the program parsing process
EXTERN SymbolTable          symbol_table;
EXTERN UpdateSimulatorQueue updateSimulatorQueue;
EXTERN thread               client;
EXTERN thread               server;
EXTERN bool                 mainIsParsing;
