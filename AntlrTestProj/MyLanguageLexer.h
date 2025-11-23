
// Generated from ./MyLanguage.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MyLanguageLexer : public antlr4::Lexer {
public:
  enum {
    FUNC = 1, CALL = 2, VAR = 3, PRINT = 4, IF = 5, ELSE = 6, WHILE = 7, 
    LBRA = 8, RBRA = 9, LPAR = 10, RPAR = 11, PLUS = 12, MINUS = 13, MULT = 14, 
    DIV = 15, REM = 16, LESS = 17, LESSEQUAL = 18, GREATER = 19, GREATEREQUAL = 20, 
    EQUAL = 21, NOTEQUAL = 22, ASSIGN = 23, SEMICOLON = 24, IDENT = 25, 
    NUMBER = 26, WS = 27
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

