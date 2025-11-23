
// Generated from ./MyLanguage.g4 by ANTLR 4.13.2


#include "MyLanguageVisitor.h"

#include "MyLanguageParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MyLanguageParserStaticData final {
  MyLanguageParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MyLanguageParserStaticData(const MyLanguageParserStaticData&) = delete;
  MyLanguageParserStaticData(MyLanguageParserStaticData&&) = delete;
  MyLanguageParserStaticData& operator=(const MyLanguageParserStaticData&) = delete;
  MyLanguageParserStaticData& operator=(MyLanguageParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mylanguageParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MyLanguageParserStaticData> mylanguageParserStaticData = nullptr;

void mylanguageParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mylanguageParserStaticData != nullptr) {
    return;
  }
#else
  assert(mylanguageParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MyLanguageParserStaticData>(
    std::vector<std::string>{
      "prog", "top_level", "func_decl", "stmt", "stmts", "if_stmt", "while_stmt", 
      "call_stmt", "var_decl_stmt", "assign_stmt", "print_stmt", "expr", 
      "summa", "term", "factor"
    },
    std::vector<std::string>{
      "", "'func'", "'call'", "'var'", "'print'", "'if'", "'else'", "'while'", 
      "'{'", "'}'", "'('", "')'", "'+'", "'-'", "'*'", "'/'", "'<'", "'='", 
      "';'"
    },
    std::vector<std::string>{
      "", "FUNC", "CALL", "VAR", "PRINT", "IF", "ELSE", "WHILE", "LBRA", 
      "RBRA", "LPAR", "RPAR", "PLUS", "MINUS", "MULT", "DIV", "LESS", "ASSIGN", 
      "SEMICOLON", "IDENT", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,21,144,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,1,0,5,0,32,8,0,10,0,12,0,35,9,0,1,1,1,1,3,1,39,8,1,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,57,8,3,1,4,5,4,60,
  	8,4,10,4,12,4,63,9,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,72,8,5,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,
  	1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,3,11,106,8,
  	11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,117,8,12,10,12,12,
  	12,120,9,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,5,13,131,8,13,
  	10,13,12,13,134,9,13,1,14,1,14,1,14,1,14,1,14,1,14,3,14,142,8,14,1,14,
  	0,2,24,26,15,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,0,0,145,0,33,1,0,
  	0,0,2,38,1,0,0,0,4,40,1,0,0,0,6,56,1,0,0,0,8,61,1,0,0,0,10,64,1,0,0,0,
  	12,73,1,0,0,0,14,79,1,0,0,0,16,83,1,0,0,0,18,89,1,0,0,0,20,94,1,0,0,0,
  	22,105,1,0,0,0,24,107,1,0,0,0,26,121,1,0,0,0,28,141,1,0,0,0,30,32,3,2,
  	1,0,31,30,1,0,0,0,32,35,1,0,0,0,33,31,1,0,0,0,33,34,1,0,0,0,34,1,1,0,
  	0,0,35,33,1,0,0,0,36,39,3,4,2,0,37,39,3,16,8,0,38,36,1,0,0,0,38,37,1,
  	0,0,0,39,3,1,0,0,0,40,41,5,1,0,0,41,42,5,19,0,0,42,43,5,8,0,0,43,44,3,
  	8,4,0,44,45,5,9,0,0,45,5,1,0,0,0,46,57,3,10,5,0,47,57,3,12,6,0,48,57,
  	3,16,8,0,49,57,3,18,9,0,50,57,3,20,10,0,51,57,3,14,7,0,52,53,5,8,0,0,
  	53,54,3,8,4,0,54,55,5,9,0,0,55,57,1,0,0,0,56,46,1,0,0,0,56,47,1,0,0,0,
  	56,48,1,0,0,0,56,49,1,0,0,0,56,50,1,0,0,0,56,51,1,0,0,0,56,52,1,0,0,0,
  	57,7,1,0,0,0,58,60,3,6,3,0,59,58,1,0,0,0,60,63,1,0,0,0,61,59,1,0,0,0,
  	61,62,1,0,0,0,62,9,1,0,0,0,63,61,1,0,0,0,64,65,5,5,0,0,65,66,5,10,0,0,
  	66,67,3,22,11,0,67,68,5,11,0,0,68,71,3,6,3,0,69,70,5,6,0,0,70,72,3,6,
  	3,0,71,69,1,0,0,0,71,72,1,0,0,0,72,11,1,0,0,0,73,74,5,7,0,0,74,75,5,10,
  	0,0,75,76,3,22,11,0,76,77,5,11,0,0,77,78,3,6,3,0,78,13,1,0,0,0,79,80,
  	5,2,0,0,80,81,5,19,0,0,81,82,5,18,0,0,82,15,1,0,0,0,83,84,5,3,0,0,84,
  	85,5,19,0,0,85,86,5,17,0,0,86,87,3,22,11,0,87,88,5,18,0,0,88,17,1,0,0,
  	0,89,90,5,19,0,0,90,91,5,17,0,0,91,92,3,22,11,0,92,93,5,18,0,0,93,19,
  	1,0,0,0,94,95,5,4,0,0,95,96,5,10,0,0,96,97,3,22,11,0,97,98,5,11,0,0,98,
  	99,5,18,0,0,99,21,1,0,0,0,100,101,3,24,12,0,101,102,5,16,0,0,102,103,
  	3,24,12,0,103,106,1,0,0,0,104,106,3,24,12,0,105,100,1,0,0,0,105,104,1,
  	0,0,0,106,23,1,0,0,0,107,108,6,12,-1,0,108,109,3,26,13,0,109,118,1,0,
  	0,0,110,111,10,3,0,0,111,112,5,12,0,0,112,117,3,26,13,0,113,114,10,2,
  	0,0,114,115,5,13,0,0,115,117,3,26,13,0,116,110,1,0,0,0,116,113,1,0,0,
  	0,117,120,1,0,0,0,118,116,1,0,0,0,118,119,1,0,0,0,119,25,1,0,0,0,120,
  	118,1,0,0,0,121,122,6,13,-1,0,122,123,3,28,14,0,123,132,1,0,0,0,124,125,
  	10,3,0,0,125,126,5,14,0,0,126,131,3,28,14,0,127,128,10,2,0,0,128,129,
  	5,15,0,0,129,131,3,28,14,0,130,124,1,0,0,0,130,127,1,0,0,0,131,134,1,
  	0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,133,27,1,0,0,0,134,132,1,0,0,0,
  	135,142,5,20,0,0,136,142,5,19,0,0,137,138,5,10,0,0,138,139,3,22,11,0,
  	139,140,5,11,0,0,140,142,1,0,0,0,141,135,1,0,0,0,141,136,1,0,0,0,141,
  	137,1,0,0,0,142,29,1,0,0,0,11,33,38,56,61,71,105,116,118,130,132,141
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mylanguageParserStaticData = std::move(staticData);
}

}

MyLanguageParser::MyLanguageParser(TokenStream *input) : MyLanguageParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MyLanguageParser::MyLanguageParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MyLanguageParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *mylanguageParserStaticData->atn, mylanguageParserStaticData->decisionToDFA, mylanguageParserStaticData->sharedContextCache, options);
}

MyLanguageParser::~MyLanguageParser() {
  delete _interpreter;
}

const atn::ATN& MyLanguageParser::getATN() const {
  return *mylanguageParserStaticData->atn;
}

std::string MyLanguageParser::getGrammarFileName() const {
  return "MyLanguage.g4";
}

const std::vector<std::string>& MyLanguageParser::getRuleNames() const {
  return mylanguageParserStaticData->ruleNames;
}

const dfa::Vocabulary& MyLanguageParser::getVocabulary() const {
  return mylanguageParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MyLanguageParser::getSerializedATN() const {
  return mylanguageParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

MyLanguageParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MyLanguageParser::Top_levelContext *> MyLanguageParser::ProgContext::top_level() {
  return getRuleContexts<MyLanguageParser::Top_levelContext>();
}

MyLanguageParser::Top_levelContext* MyLanguageParser::ProgContext::top_level(size_t i) {
  return getRuleContext<MyLanguageParser::Top_levelContext>(i);
}


size_t MyLanguageParser::ProgContext::getRuleIndex() const {
  return MyLanguageParser::RuleProg;
}


std::any MyLanguageParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::ProgContext* MyLanguageParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, MyLanguageParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MyLanguageParser::FUNC

    || _la == MyLanguageParser::VAR) {
      setState(30);
      top_level();
      setState(35);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Top_levelContext ------------------------------------------------------------------

MyLanguageParser::Top_levelContext::Top_levelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::Func_declContext* MyLanguageParser::Top_levelContext::func_decl() {
  return getRuleContext<MyLanguageParser::Func_declContext>(0);
}

MyLanguageParser::Var_decl_stmtContext* MyLanguageParser::Top_levelContext::var_decl_stmt() {
  return getRuleContext<MyLanguageParser::Var_decl_stmtContext>(0);
}


size_t MyLanguageParser::Top_levelContext::getRuleIndex() const {
  return MyLanguageParser::RuleTop_level;
}


std::any MyLanguageParser::Top_levelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitTop_level(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::Top_levelContext* MyLanguageParser::top_level() {
  Top_levelContext *_localctx = _tracker.createInstance<Top_levelContext>(_ctx, getState());
  enterRule(_localctx, 2, MyLanguageParser::RuleTop_level);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(38);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MyLanguageParser::FUNC: {
        enterOuterAlt(_localctx, 1);
        setState(36);
        func_decl();
        break;
      }

      case MyLanguageParser::VAR: {
        enterOuterAlt(_localctx, 2);
        setState(37);
        var_decl_stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_declContext ------------------------------------------------------------------

MyLanguageParser::Func_declContext::Func_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::Func_declContext::FUNC() {
  return getToken(MyLanguageParser::FUNC, 0);
}

tree::TerminalNode* MyLanguageParser::Func_declContext::IDENT() {
  return getToken(MyLanguageParser::IDENT, 0);
}

tree::TerminalNode* MyLanguageParser::Func_declContext::LBRA() {
  return getToken(MyLanguageParser::LBRA, 0);
}

MyLanguageParser::StmtsContext* MyLanguageParser::Func_declContext::stmts() {
  return getRuleContext<MyLanguageParser::StmtsContext>(0);
}

tree::TerminalNode* MyLanguageParser::Func_declContext::RBRA() {
  return getToken(MyLanguageParser::RBRA, 0);
}


size_t MyLanguageParser::Func_declContext::getRuleIndex() const {
  return MyLanguageParser::RuleFunc_decl;
}


std::any MyLanguageParser::Func_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitFunc_decl(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::Func_declContext* MyLanguageParser::func_decl() {
  Func_declContext *_localctx = _tracker.createInstance<Func_declContext>(_ctx, getState());
  enterRule(_localctx, 4, MyLanguageParser::RuleFunc_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    match(MyLanguageParser::FUNC);
    setState(41);
    match(MyLanguageParser::IDENT);
    setState(42);
    match(MyLanguageParser::LBRA);
    setState(43);
    stmts();
    setState(44);
    match(MyLanguageParser::RBRA);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

MyLanguageParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::If_stmtContext* MyLanguageParser::StmtContext::if_stmt() {
  return getRuleContext<MyLanguageParser::If_stmtContext>(0);
}

MyLanguageParser::While_stmtContext* MyLanguageParser::StmtContext::while_stmt() {
  return getRuleContext<MyLanguageParser::While_stmtContext>(0);
}

MyLanguageParser::Var_decl_stmtContext* MyLanguageParser::StmtContext::var_decl_stmt() {
  return getRuleContext<MyLanguageParser::Var_decl_stmtContext>(0);
}

MyLanguageParser::Assign_stmtContext* MyLanguageParser::StmtContext::assign_stmt() {
  return getRuleContext<MyLanguageParser::Assign_stmtContext>(0);
}

MyLanguageParser::Print_stmtContext* MyLanguageParser::StmtContext::print_stmt() {
  return getRuleContext<MyLanguageParser::Print_stmtContext>(0);
}

MyLanguageParser::Call_stmtContext* MyLanguageParser::StmtContext::call_stmt() {
  return getRuleContext<MyLanguageParser::Call_stmtContext>(0);
}

tree::TerminalNode* MyLanguageParser::StmtContext::LBRA() {
  return getToken(MyLanguageParser::LBRA, 0);
}

MyLanguageParser::StmtsContext* MyLanguageParser::StmtContext::stmts() {
  return getRuleContext<MyLanguageParser::StmtsContext>(0);
}

tree::TerminalNode* MyLanguageParser::StmtContext::RBRA() {
  return getToken(MyLanguageParser::RBRA, 0);
}


size_t MyLanguageParser::StmtContext::getRuleIndex() const {
  return MyLanguageParser::RuleStmt;
}


std::any MyLanguageParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::StmtContext* MyLanguageParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 6, MyLanguageParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(56);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MyLanguageParser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(46);
        if_stmt();
        break;
      }

      case MyLanguageParser::WHILE: {
        enterOuterAlt(_localctx, 2);
        setState(47);
        while_stmt();
        break;
      }

      case MyLanguageParser::VAR: {
        enterOuterAlt(_localctx, 3);
        setState(48);
        var_decl_stmt();
        break;
      }

      case MyLanguageParser::IDENT: {
        enterOuterAlt(_localctx, 4);
        setState(49);
        assign_stmt();
        break;
      }

      case MyLanguageParser::PRINT: {
        enterOuterAlt(_localctx, 5);
        setState(50);
        print_stmt();
        break;
      }

      case MyLanguageParser::CALL: {
        enterOuterAlt(_localctx, 6);
        setState(51);
        call_stmt();
        break;
      }

      case MyLanguageParser::LBRA: {
        enterOuterAlt(_localctx, 7);
        setState(52);
        match(MyLanguageParser::LBRA);
        setState(53);
        stmts();
        setState(54);
        match(MyLanguageParser::RBRA);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtsContext ------------------------------------------------------------------

MyLanguageParser::StmtsContext::StmtsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MyLanguageParser::StmtContext *> MyLanguageParser::StmtsContext::stmt() {
  return getRuleContexts<MyLanguageParser::StmtContext>();
}

MyLanguageParser::StmtContext* MyLanguageParser::StmtsContext::stmt(size_t i) {
  return getRuleContext<MyLanguageParser::StmtContext>(i);
}


size_t MyLanguageParser::StmtsContext::getRuleIndex() const {
  return MyLanguageParser::RuleStmts;
}


std::any MyLanguageParser::StmtsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitStmts(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::StmtsContext* MyLanguageParser::stmts() {
  StmtsContext *_localctx = _tracker.createInstance<StmtsContext>(_ctx, getState());
  enterRule(_localctx, 8, MyLanguageParser::RuleStmts);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 524732) != 0)) {
      setState(58);
      stmt();
      setState(63);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_stmtContext ------------------------------------------------------------------

MyLanguageParser::If_stmtContext::If_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::If_stmtContext::IF() {
  return getToken(MyLanguageParser::IF, 0);
}

tree::TerminalNode* MyLanguageParser::If_stmtContext::LPAR() {
  return getToken(MyLanguageParser::LPAR, 0);
}

MyLanguageParser::ExprContext* MyLanguageParser::If_stmtContext::expr() {
  return getRuleContext<MyLanguageParser::ExprContext>(0);
}

tree::TerminalNode* MyLanguageParser::If_stmtContext::RPAR() {
  return getToken(MyLanguageParser::RPAR, 0);
}

std::vector<MyLanguageParser::StmtContext *> MyLanguageParser::If_stmtContext::stmt() {
  return getRuleContexts<MyLanguageParser::StmtContext>();
}

MyLanguageParser::StmtContext* MyLanguageParser::If_stmtContext::stmt(size_t i) {
  return getRuleContext<MyLanguageParser::StmtContext>(i);
}

tree::TerminalNode* MyLanguageParser::If_stmtContext::ELSE() {
  return getToken(MyLanguageParser::ELSE, 0);
}


size_t MyLanguageParser::If_stmtContext::getRuleIndex() const {
  return MyLanguageParser::RuleIf_stmt;
}


std::any MyLanguageParser::If_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitIf_stmt(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::If_stmtContext* MyLanguageParser::if_stmt() {
  If_stmtContext *_localctx = _tracker.createInstance<If_stmtContext>(_ctx, getState());
  enterRule(_localctx, 10, MyLanguageParser::RuleIf_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(MyLanguageParser::IF);
    setState(65);
    match(MyLanguageParser::LPAR);
    setState(66);
    expr();
    setState(67);
    match(MyLanguageParser::RPAR);
    setState(68);
    stmt();
    setState(71);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(69);
      match(MyLanguageParser::ELSE);
      setState(70);
      stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_stmtContext ------------------------------------------------------------------

MyLanguageParser::While_stmtContext::While_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::While_stmtContext::WHILE() {
  return getToken(MyLanguageParser::WHILE, 0);
}

tree::TerminalNode* MyLanguageParser::While_stmtContext::LPAR() {
  return getToken(MyLanguageParser::LPAR, 0);
}

MyLanguageParser::ExprContext* MyLanguageParser::While_stmtContext::expr() {
  return getRuleContext<MyLanguageParser::ExprContext>(0);
}

tree::TerminalNode* MyLanguageParser::While_stmtContext::RPAR() {
  return getToken(MyLanguageParser::RPAR, 0);
}

MyLanguageParser::StmtContext* MyLanguageParser::While_stmtContext::stmt() {
  return getRuleContext<MyLanguageParser::StmtContext>(0);
}


size_t MyLanguageParser::While_stmtContext::getRuleIndex() const {
  return MyLanguageParser::RuleWhile_stmt;
}


std::any MyLanguageParser::While_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitWhile_stmt(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::While_stmtContext* MyLanguageParser::while_stmt() {
  While_stmtContext *_localctx = _tracker.createInstance<While_stmtContext>(_ctx, getState());
  enterRule(_localctx, 12, MyLanguageParser::RuleWhile_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    match(MyLanguageParser::WHILE);
    setState(74);
    match(MyLanguageParser::LPAR);
    setState(75);
    expr();
    setState(76);
    match(MyLanguageParser::RPAR);
    setState(77);
    stmt();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Call_stmtContext ------------------------------------------------------------------

MyLanguageParser::Call_stmtContext::Call_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::Call_stmtContext::CALL() {
  return getToken(MyLanguageParser::CALL, 0);
}

tree::TerminalNode* MyLanguageParser::Call_stmtContext::IDENT() {
  return getToken(MyLanguageParser::IDENT, 0);
}

tree::TerminalNode* MyLanguageParser::Call_stmtContext::SEMICOLON() {
  return getToken(MyLanguageParser::SEMICOLON, 0);
}


size_t MyLanguageParser::Call_stmtContext::getRuleIndex() const {
  return MyLanguageParser::RuleCall_stmt;
}


std::any MyLanguageParser::Call_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitCall_stmt(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::Call_stmtContext* MyLanguageParser::call_stmt() {
  Call_stmtContext *_localctx = _tracker.createInstance<Call_stmtContext>(_ctx, getState());
  enterRule(_localctx, 14, MyLanguageParser::RuleCall_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    match(MyLanguageParser::CALL);
    setState(80);
    match(MyLanguageParser::IDENT);
    setState(81);
    match(MyLanguageParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_decl_stmtContext ------------------------------------------------------------------

MyLanguageParser::Var_decl_stmtContext::Var_decl_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::Var_decl_stmtContext::VAR() {
  return getToken(MyLanguageParser::VAR, 0);
}

tree::TerminalNode* MyLanguageParser::Var_decl_stmtContext::IDENT() {
  return getToken(MyLanguageParser::IDENT, 0);
}

tree::TerminalNode* MyLanguageParser::Var_decl_stmtContext::ASSIGN() {
  return getToken(MyLanguageParser::ASSIGN, 0);
}

MyLanguageParser::ExprContext* MyLanguageParser::Var_decl_stmtContext::expr() {
  return getRuleContext<MyLanguageParser::ExprContext>(0);
}

tree::TerminalNode* MyLanguageParser::Var_decl_stmtContext::SEMICOLON() {
  return getToken(MyLanguageParser::SEMICOLON, 0);
}


size_t MyLanguageParser::Var_decl_stmtContext::getRuleIndex() const {
  return MyLanguageParser::RuleVar_decl_stmt;
}


std::any MyLanguageParser::Var_decl_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitVar_decl_stmt(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::Var_decl_stmtContext* MyLanguageParser::var_decl_stmt() {
  Var_decl_stmtContext *_localctx = _tracker.createInstance<Var_decl_stmtContext>(_ctx, getState());
  enterRule(_localctx, 16, MyLanguageParser::RuleVar_decl_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    match(MyLanguageParser::VAR);
    setState(84);
    match(MyLanguageParser::IDENT);
    setState(85);
    match(MyLanguageParser::ASSIGN);
    setState(86);
    expr();
    setState(87);
    match(MyLanguageParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assign_stmtContext ------------------------------------------------------------------

MyLanguageParser::Assign_stmtContext::Assign_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::Assign_stmtContext::IDENT() {
  return getToken(MyLanguageParser::IDENT, 0);
}

tree::TerminalNode* MyLanguageParser::Assign_stmtContext::ASSIGN() {
  return getToken(MyLanguageParser::ASSIGN, 0);
}

MyLanguageParser::ExprContext* MyLanguageParser::Assign_stmtContext::expr() {
  return getRuleContext<MyLanguageParser::ExprContext>(0);
}

tree::TerminalNode* MyLanguageParser::Assign_stmtContext::SEMICOLON() {
  return getToken(MyLanguageParser::SEMICOLON, 0);
}


size_t MyLanguageParser::Assign_stmtContext::getRuleIndex() const {
  return MyLanguageParser::RuleAssign_stmt;
}


std::any MyLanguageParser::Assign_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitAssign_stmt(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::Assign_stmtContext* MyLanguageParser::assign_stmt() {
  Assign_stmtContext *_localctx = _tracker.createInstance<Assign_stmtContext>(_ctx, getState());
  enterRule(_localctx, 18, MyLanguageParser::RuleAssign_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    match(MyLanguageParser::IDENT);
    setState(90);
    match(MyLanguageParser::ASSIGN);
    setState(91);
    expr();
    setState(92);
    match(MyLanguageParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Print_stmtContext ------------------------------------------------------------------

MyLanguageParser::Print_stmtContext::Print_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::Print_stmtContext::PRINT() {
  return getToken(MyLanguageParser::PRINT, 0);
}

tree::TerminalNode* MyLanguageParser::Print_stmtContext::LPAR() {
  return getToken(MyLanguageParser::LPAR, 0);
}

MyLanguageParser::ExprContext* MyLanguageParser::Print_stmtContext::expr() {
  return getRuleContext<MyLanguageParser::ExprContext>(0);
}

tree::TerminalNode* MyLanguageParser::Print_stmtContext::RPAR() {
  return getToken(MyLanguageParser::RPAR, 0);
}

tree::TerminalNode* MyLanguageParser::Print_stmtContext::SEMICOLON() {
  return getToken(MyLanguageParser::SEMICOLON, 0);
}


size_t MyLanguageParser::Print_stmtContext::getRuleIndex() const {
  return MyLanguageParser::RulePrint_stmt;
}


std::any MyLanguageParser::Print_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitPrint_stmt(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::Print_stmtContext* MyLanguageParser::print_stmt() {
  Print_stmtContext *_localctx = _tracker.createInstance<Print_stmtContext>(_ctx, getState());
  enterRule(_localctx, 20, MyLanguageParser::RulePrint_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    match(MyLanguageParser::PRINT);
    setState(95);
    match(MyLanguageParser::LPAR);
    setState(96);
    expr();
    setState(97);
    match(MyLanguageParser::RPAR);
    setState(98);
    match(MyLanguageParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MyLanguageParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MyLanguageParser::SummaContext *> MyLanguageParser::ExprContext::summa() {
  return getRuleContexts<MyLanguageParser::SummaContext>();
}

MyLanguageParser::SummaContext* MyLanguageParser::ExprContext::summa(size_t i) {
  return getRuleContext<MyLanguageParser::SummaContext>(i);
}

tree::TerminalNode* MyLanguageParser::ExprContext::LESS() {
  return getToken(MyLanguageParser::LESS, 0);
}


size_t MyLanguageParser::ExprContext::getRuleIndex() const {
  return MyLanguageParser::RuleExpr;
}


std::any MyLanguageParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::ExprContext* MyLanguageParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 22, MyLanguageParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(105);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(100);
      summa(0);
      setState(101);
      match(MyLanguageParser::LESS);
      setState(102);
      summa(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(104);
      summa(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SummaContext ------------------------------------------------------------------

MyLanguageParser::SummaContext::SummaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::TermContext* MyLanguageParser::SummaContext::term() {
  return getRuleContext<MyLanguageParser::TermContext>(0);
}

MyLanguageParser::SummaContext* MyLanguageParser::SummaContext::summa() {
  return getRuleContext<MyLanguageParser::SummaContext>(0);
}

tree::TerminalNode* MyLanguageParser::SummaContext::PLUS() {
  return getToken(MyLanguageParser::PLUS, 0);
}

tree::TerminalNode* MyLanguageParser::SummaContext::MINUS() {
  return getToken(MyLanguageParser::MINUS, 0);
}


size_t MyLanguageParser::SummaContext::getRuleIndex() const {
  return MyLanguageParser::RuleSumma;
}


std::any MyLanguageParser::SummaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitSumma(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::SummaContext* MyLanguageParser::summa() {
   return summa(0);
}

MyLanguageParser::SummaContext* MyLanguageParser::summa(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::SummaContext *_localctx = _tracker.createInstance<SummaContext>(_ctx, parentState);
  MyLanguageParser::SummaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, MyLanguageParser::RuleSumma, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(108);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(118);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(116);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SummaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSumma);
          setState(110);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(111);
          match(MyLanguageParser::PLUS);
          setState(112);
          term(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SummaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSumma);
          setState(113);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(114);
          match(MyLanguageParser::MINUS);
          setState(115);
          term(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(120);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

MyLanguageParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::FactorContext* MyLanguageParser::TermContext::factor() {
  return getRuleContext<MyLanguageParser::FactorContext>(0);
}

MyLanguageParser::TermContext* MyLanguageParser::TermContext::term() {
  return getRuleContext<MyLanguageParser::TermContext>(0);
}

tree::TerminalNode* MyLanguageParser::TermContext::MULT() {
  return getToken(MyLanguageParser::MULT, 0);
}

tree::TerminalNode* MyLanguageParser::TermContext::DIV() {
  return getToken(MyLanguageParser::DIV, 0);
}


size_t MyLanguageParser::TermContext::getRuleIndex() const {
  return MyLanguageParser::RuleTerm;
}


std::any MyLanguageParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::TermContext* MyLanguageParser::term() {
   return term(0);
}

MyLanguageParser::TermContext* MyLanguageParser::term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, parentState);
  MyLanguageParser::TermContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, MyLanguageParser::RuleTerm, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(122);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(132);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(130);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(124);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(125);
          match(MyLanguageParser::MULT);
          setState(126);
          factor();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(127);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(128);
          match(MyLanguageParser::DIV);
          setState(129);
          factor();
          break;
        }

        default:
          break;
        } 
      }
      setState(134);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

MyLanguageParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyLanguageParser::FactorContext::NUMBER() {
  return getToken(MyLanguageParser::NUMBER, 0);
}

tree::TerminalNode* MyLanguageParser::FactorContext::IDENT() {
  return getToken(MyLanguageParser::IDENT, 0);
}

tree::TerminalNode* MyLanguageParser::FactorContext::LPAR() {
  return getToken(MyLanguageParser::LPAR, 0);
}

MyLanguageParser::ExprContext* MyLanguageParser::FactorContext::expr() {
  return getRuleContext<MyLanguageParser::ExprContext>(0);
}

tree::TerminalNode* MyLanguageParser::FactorContext::RPAR() {
  return getToken(MyLanguageParser::RPAR, 0);
}


size_t MyLanguageParser::FactorContext::getRuleIndex() const {
  return MyLanguageParser::RuleFactor;
}


std::any MyLanguageParser::FactorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitFactor(this);
  else
    return visitor->visitChildren(this);
}

MyLanguageParser::FactorContext* MyLanguageParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 28, MyLanguageParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(141);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MyLanguageParser::NUMBER: {
        enterOuterAlt(_localctx, 1);
        setState(135);
        match(MyLanguageParser::NUMBER);
        break;
      }

      case MyLanguageParser::IDENT: {
        enterOuterAlt(_localctx, 2);
        setState(136);
        match(MyLanguageParser::IDENT);
        break;
      }

      case MyLanguageParser::LPAR: {
        enterOuterAlt(_localctx, 3);
        setState(137);
        match(MyLanguageParser::LPAR);
        setState(138);
        expr();
        setState(139);
        match(MyLanguageParser::RPAR);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool MyLanguageParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 12: return summaSempred(antlrcpp::downCast<SummaContext *>(context), predicateIndex);
    case 13: return termSempred(antlrcpp::downCast<TermContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::summaSempred(SummaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 3);
    case 3: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void MyLanguageParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mylanguageParserInitialize();
#else
  ::antlr4::internal::call_once(mylanguageParserOnceFlag, mylanguageParserInitialize);
#endif
}
