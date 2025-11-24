
// Generated from ./MyLanguage.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MyLanguageLexer : public antlr4::Lexer {
public:
  enum {
    FUNC = 1, CALL = 2, VAR = 3, PRINT = 4, IF = 5, ELSE = 6, WHILE = 7, 
    LBRA = 8, RBRA = 9, LPAR = 10, RPAR = 11, PLUS = 12, MINUS = 13, MULT = 14, 
    DIV = 15, REM = 16, LESS = 17, LESSEQUAL = 18, GREATER = 19, GREATEREQUAL = 20, 
    EQUAL = 21, NOTEQUAL = 22, BITNOT = 23, BITOR = 24, BITAND = 25, BITXOR = 26, 
    SHIFTLEFT = 27, SHIFTRIGHT = 28, ASSIGN = 29, SEMICOLON = 30, IDENT = 31, 
    NUMBER = 32, WS = 33, LINE_COMMENT = 34, BLOCK_COMMENT = 35
  };

  explicit MyLanguageLexer(antlr4::CharStream *input);

  ~MyLanguageLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

