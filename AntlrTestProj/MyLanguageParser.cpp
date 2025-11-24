
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
      "bitwiseor", "bitwisexor", "bitwiseand", "eqcomparison", "comparison", 
      "shift", "summa", "term", "factor"
    },
    std::vector<std::string>{
      "", "'func'", "'call'", "'var'", "'print'", "'if'", "'else'", "'while'", 
      "'{'", "'}'", "'('", "')'", "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", 
      "'<='", "'>'", "'>='", "'=='", "'!='", "'~'", "'|'", "'&'", "'^'", 
      "'<<'", "'>>'", "'='", "';'"
    },
    std::vector<std::string>{
      "", "FUNC", "CALL", "VAR", "PRINT", "IF", "ELSE", "WHILE", "LBRA", 
      "RBRA", "LPAR", "RPAR", "PLUS", "MINUS", "MULT", "DIV", "REM", "LESS", 
      "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL", "BITNOT", 
      "BITOR", "BITAND", "BITXOR", "SHIFTLEFT", "SHIFTRIGHT", "ASSIGN", 
      "SEMICOLON", "IDENT", "NUMBER", "WS", "LINE_COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,35,239,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,5,
  	0,44,8,0,10,0,12,0,47,9,0,1,1,1,1,3,1,51,8,1,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,69,8,3,1,4,5,4,72,8,4,10,
  	4,12,4,75,9,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,84,8,5,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,
  	10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,5,
  	12,121,8,12,10,12,12,12,124,9,12,1,13,1,13,1,13,1,13,1,13,1,13,5,13,132,
  	8,13,10,13,12,13,135,9,13,1,14,1,14,1,14,1,14,1,14,1,14,5,14,143,8,14,
  	10,14,12,14,146,9,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,5,15,
  	157,8,15,10,15,12,15,160,9,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,5,16,177,8,16,10,16,12,16,180,9,16,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,5,17,191,8,17,10,17,12,17,
  	194,9,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,5,18,205,8,18,10,
  	18,12,18,208,9,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,
  	19,1,19,5,19,222,8,19,10,19,12,19,225,9,19,1,20,1,20,1,20,1,20,1,20,1,
  	20,1,20,1,20,1,20,1,20,3,20,237,8,20,1,20,0,8,24,26,28,30,32,34,36,38,
  	21,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0,0,247,
  	0,45,1,0,0,0,2,50,1,0,0,0,4,52,1,0,0,0,6,68,1,0,0,0,8,73,1,0,0,0,10,76,
  	1,0,0,0,12,85,1,0,0,0,14,91,1,0,0,0,16,95,1,0,0,0,18,101,1,0,0,0,20,106,
  	1,0,0,0,22,112,1,0,0,0,24,114,1,0,0,0,26,125,1,0,0,0,28,136,1,0,0,0,30,
  	147,1,0,0,0,32,161,1,0,0,0,34,181,1,0,0,0,36,195,1,0,0,0,38,209,1,0,0,
  	0,40,236,1,0,0,0,42,44,3,2,1,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,
  	0,0,45,46,1,0,0,0,46,1,1,0,0,0,47,45,1,0,0,0,48,51,3,4,2,0,49,51,3,16,
  	8,0,50,48,1,0,0,0,50,49,1,0,0,0,51,3,1,0,0,0,52,53,5,1,0,0,53,54,5,31,
  	0,0,54,55,5,8,0,0,55,56,3,8,4,0,56,57,5,9,0,0,57,5,1,0,0,0,58,69,3,10,
  	5,0,59,69,3,12,6,0,60,69,3,16,8,0,61,69,3,18,9,0,62,69,3,20,10,0,63,69,
  	3,14,7,0,64,65,5,8,0,0,65,66,3,8,4,0,66,67,5,9,0,0,67,69,1,0,0,0,68,58,
  	1,0,0,0,68,59,1,0,0,0,68,60,1,0,0,0,68,61,1,0,0,0,68,62,1,0,0,0,68,63,
  	1,0,0,0,68,64,1,0,0,0,69,7,1,0,0,0,70,72,3,6,3,0,71,70,1,0,0,0,72,75,
  	1,0,0,0,73,71,1,0,0,0,73,74,1,0,0,0,74,9,1,0,0,0,75,73,1,0,0,0,76,77,
  	5,5,0,0,77,78,5,10,0,0,78,79,3,22,11,0,79,80,5,11,0,0,80,83,3,6,3,0,81,
  	82,5,6,0,0,82,84,3,6,3,0,83,81,1,0,0,0,83,84,1,0,0,0,84,11,1,0,0,0,85,
  	86,5,7,0,0,86,87,5,10,0,0,87,88,3,22,11,0,88,89,5,11,0,0,89,90,3,6,3,
  	0,90,13,1,0,0,0,91,92,5,2,0,0,92,93,5,31,0,0,93,94,5,30,0,0,94,15,1,0,
  	0,0,95,96,5,3,0,0,96,97,5,31,0,0,97,98,5,29,0,0,98,99,3,22,11,0,99,100,
  	5,30,0,0,100,17,1,0,0,0,101,102,5,31,0,0,102,103,5,29,0,0,103,104,3,22,
  	11,0,104,105,5,30,0,0,105,19,1,0,0,0,106,107,5,4,0,0,107,108,5,10,0,0,
  	108,109,3,22,11,0,109,110,5,11,0,0,110,111,5,30,0,0,111,21,1,0,0,0,112,
  	113,3,24,12,0,113,23,1,0,0,0,114,115,6,12,-1,0,115,116,3,26,13,0,116,
  	122,1,0,0,0,117,118,10,2,0,0,118,119,5,24,0,0,119,121,3,26,13,0,120,117,
  	1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,122,123,1,0,0,0,123,25,1,0,0,
  	0,124,122,1,0,0,0,125,126,6,13,-1,0,126,127,3,28,14,0,127,133,1,0,0,0,
  	128,129,10,2,0,0,129,130,5,26,0,0,130,132,3,28,14,0,131,128,1,0,0,0,132,
  	135,1,0,0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,27,1,0,0,0,135,133,1,
  	0,0,0,136,137,6,14,-1,0,137,138,3,30,15,0,138,144,1,0,0,0,139,140,10,
  	2,0,0,140,141,5,25,0,0,141,143,3,30,15,0,142,139,1,0,0,0,143,146,1,0,
  	0,0,144,142,1,0,0,0,144,145,1,0,0,0,145,29,1,0,0,0,146,144,1,0,0,0,147,
  	148,6,15,-1,0,148,149,3,32,16,0,149,158,1,0,0,0,150,151,10,3,0,0,151,
  	152,5,21,0,0,152,157,3,32,16,0,153,154,10,2,0,0,154,155,5,22,0,0,155,
  	157,3,32,16,0,156,150,1,0,0,0,156,153,1,0,0,0,157,160,1,0,0,0,158,156,
  	1,0,0,0,158,159,1,0,0,0,159,31,1,0,0,0,160,158,1,0,0,0,161,162,6,16,-1,
  	0,162,163,3,34,17,0,163,178,1,0,0,0,164,165,10,5,0,0,165,166,5,17,0,0,
  	166,177,3,34,17,0,167,168,10,4,0,0,168,169,5,18,0,0,169,177,3,34,17,0,
  	170,171,10,3,0,0,171,172,5,19,0,0,172,177,3,34,17,0,173,174,10,2,0,0,
  	174,175,5,20,0,0,175,177,3,34,17,0,176,164,1,0,0,0,176,167,1,0,0,0,176,
  	170,1,0,0,0,176,173,1,0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,178,179,1,
  	0,0,0,179,33,1,0,0,0,180,178,1,0,0,0,181,182,6,17,-1,0,182,183,3,36,18,
  	0,183,192,1,0,0,0,184,185,10,3,0,0,185,186,5,27,0,0,186,191,3,36,18,0,
  	187,188,10,2,0,0,188,189,5,28,0,0,189,191,3,36,18,0,190,184,1,0,0,0,190,
  	187,1,0,0,0,191,194,1,0,0,0,192,190,1,0,0,0,192,193,1,0,0,0,193,35,1,
  	0,0,0,194,192,1,0,0,0,195,196,6,18,-1,0,196,197,3,38,19,0,197,206,1,0,
  	0,0,198,199,10,3,0,0,199,200,5,12,0,0,200,205,3,38,19,0,201,202,10,2,
  	0,0,202,203,5,13,0,0,203,205,3,38,19,0,204,198,1,0,0,0,204,201,1,0,0,
  	0,205,208,1,0,0,0,206,204,1,0,0,0,206,207,1,0,0,0,207,37,1,0,0,0,208,
  	206,1,0,0,0,209,210,6,19,-1,0,210,211,3,40,20,0,211,223,1,0,0,0,212,213,
  	10,4,0,0,213,214,5,14,0,0,214,222,3,40,20,0,215,216,10,3,0,0,216,217,
  	5,15,0,0,217,222,3,40,20,0,218,219,10,2,0,0,219,220,5,16,0,0,220,222,
  	3,40,20,0,221,212,1,0,0,0,221,215,1,0,0,0,221,218,1,0,0,0,222,225,1,0,
  	0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,39,1,0,0,0,225,223,1,0,0,0,226,
  	227,5,13,0,0,227,237,3,40,20,0,228,229,5,23,0,0,229,237,3,40,20,0,230,
  	237,5,32,0,0,231,237,5,31,0,0,232,233,5,10,0,0,233,234,3,22,11,0,234,
  	235,5,11,0,0,235,237,1,0,0,0,236,226,1,0,0,0,236,228,1,0,0,0,236,230,
  	1,0,0,0,236,231,1,0,0,0,236,232,1,0,0,0,237,41,1,0,0,0,19,45,50,68,73,
  	83,122,133,144,156,158,176,178,190,192,204,206,221,223,236
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
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MyLanguageParser::FUNC

    || _la == MyLanguageParser::VAR) {
      setState(42);
      top_level();
      setState(47);
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
    setState(50);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MyLanguageParser::FUNC: {
        enterOuterAlt(_localctx, 1);
        setState(48);
        func_decl();
        break;
      }

      case MyLanguageParser::VAR: {
        enterOuterAlt(_localctx, 2);
        setState(49);
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
    setState(52);
    match(MyLanguageParser::FUNC);
    setState(53);
    match(MyLanguageParser::IDENT);
    setState(54);
    match(MyLanguageParser::LBRA);
    setState(55);
    stmts();
    setState(56);
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
    setState(68);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MyLanguageParser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(58);
        if_stmt();
        break;
      }

      case MyLanguageParser::WHILE: {
        enterOuterAlt(_localctx, 2);
        setState(59);
        while_stmt();
        break;
      }

      case MyLanguageParser::VAR: {
        enterOuterAlt(_localctx, 3);
        setState(60);
        var_decl_stmt();
        break;
      }

      case MyLanguageParser::IDENT: {
        enterOuterAlt(_localctx, 4);
        setState(61);
        assign_stmt();
        break;
      }

      case MyLanguageParser::PRINT: {
        enterOuterAlt(_localctx, 5);
        setState(62);
        print_stmt();
        break;
      }

      case MyLanguageParser::CALL: {
        enterOuterAlt(_localctx, 6);
        setState(63);
        call_stmt();
        break;
      }

      case MyLanguageParser::LBRA: {
        enterOuterAlt(_localctx, 7);
        setState(64);
        match(MyLanguageParser::LBRA);
        setState(65);
        stmts();
        setState(66);
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
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2147484092) != 0)) {
      setState(70);
      stmt();
      setState(75);
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
    setState(76);
    match(MyLanguageParser::IF);
    setState(77);
    match(MyLanguageParser::LPAR);
    setState(78);
    expr();
    setState(79);
    match(MyLanguageParser::RPAR);
    setState(80);
    stmt();
    setState(83);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(81);
      match(MyLanguageParser::ELSE);
      setState(82);
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
    setState(85);
    match(MyLanguageParser::WHILE);
    setState(86);
    match(MyLanguageParser::LPAR);
    setState(87);
    expr();
    setState(88);
    match(MyLanguageParser::RPAR);
    setState(89);
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
    setState(91);
    match(MyLanguageParser::CALL);
    setState(92);
    match(MyLanguageParser::IDENT);
    setState(93);
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
    setState(95);
    match(MyLanguageParser::VAR);
    setState(96);
    match(MyLanguageParser::IDENT);
    setState(97);
    match(MyLanguageParser::ASSIGN);
    setState(98);
    expr();
    setState(99);
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
    setState(101);
    match(MyLanguageParser::IDENT);
    setState(102);
    match(MyLanguageParser::ASSIGN);
    setState(103);
    expr();
    setState(104);
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
    setState(106);
    match(MyLanguageParser::PRINT);
    setState(107);
    match(MyLanguageParser::LPAR);
    setState(108);
    expr();
    setState(109);
    match(MyLanguageParser::RPAR);
    setState(110);
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

MyLanguageParser::BitwiseorContext* MyLanguageParser::ExprContext::bitwiseor() {
  return getRuleContext<MyLanguageParser::BitwiseorContext>(0);
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
    enterOuterAlt(_localctx, 1);
    setState(112);
    bitwiseor(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseorContext ------------------------------------------------------------------

MyLanguageParser::BitwiseorContext::BitwiseorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::BitwisexorContext* MyLanguageParser::BitwiseorContext::bitwisexor() {
  return getRuleContext<MyLanguageParser::BitwisexorContext>(0);
}

MyLanguageParser::BitwiseorContext* MyLanguageParser::BitwiseorContext::bitwiseor() {
  return getRuleContext<MyLanguageParser::BitwiseorContext>(0);
}

tree::TerminalNode* MyLanguageParser::BitwiseorContext::BITOR() {
  return getToken(MyLanguageParser::BITOR, 0);
}


size_t MyLanguageParser::BitwiseorContext::getRuleIndex() const {
  return MyLanguageParser::RuleBitwiseor;
}


std::any MyLanguageParser::BitwiseorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitBitwiseor(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::BitwiseorContext* MyLanguageParser::bitwiseor() {
   return bitwiseor(0);
}

MyLanguageParser::BitwiseorContext* MyLanguageParser::bitwiseor(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::BitwiseorContext *_localctx = _tracker.createInstance<BitwiseorContext>(_ctx, parentState);
  MyLanguageParser::BitwiseorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, MyLanguageParser::RuleBitwiseor, precedence);

    

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
    setState(115);
    bitwisexor(0);
    _ctx->stop = _input->LT(-1);
    setState(122);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<BitwiseorContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBitwiseor);
        setState(117);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(118);
        match(MyLanguageParser::BITOR);
        setState(119);
        bitwisexor(0); 
      }
      setState(124);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- BitwisexorContext ------------------------------------------------------------------

MyLanguageParser::BitwisexorContext::BitwisexorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::BitwiseandContext* MyLanguageParser::BitwisexorContext::bitwiseand() {
  return getRuleContext<MyLanguageParser::BitwiseandContext>(0);
}

MyLanguageParser::BitwisexorContext* MyLanguageParser::BitwisexorContext::bitwisexor() {
  return getRuleContext<MyLanguageParser::BitwisexorContext>(0);
}

tree::TerminalNode* MyLanguageParser::BitwisexorContext::BITXOR() {
  return getToken(MyLanguageParser::BITXOR, 0);
}


size_t MyLanguageParser::BitwisexorContext::getRuleIndex() const {
  return MyLanguageParser::RuleBitwisexor;
}


std::any MyLanguageParser::BitwisexorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitBitwisexor(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::BitwisexorContext* MyLanguageParser::bitwisexor() {
   return bitwisexor(0);
}

MyLanguageParser::BitwisexorContext* MyLanguageParser::bitwisexor(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::BitwisexorContext *_localctx = _tracker.createInstance<BitwisexorContext>(_ctx, parentState);
  MyLanguageParser::BitwisexorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, MyLanguageParser::RuleBitwisexor, precedence);

    

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
    setState(126);
    bitwiseand(0);
    _ctx->stop = _input->LT(-1);
    setState(133);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<BitwisexorContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBitwisexor);
        setState(128);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(129);
        match(MyLanguageParser::BITXOR);
        setState(130);
        bitwiseand(0); 
      }
      setState(135);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- BitwiseandContext ------------------------------------------------------------------

MyLanguageParser::BitwiseandContext::BitwiseandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::EqcomparisonContext* MyLanguageParser::BitwiseandContext::eqcomparison() {
  return getRuleContext<MyLanguageParser::EqcomparisonContext>(0);
}

MyLanguageParser::BitwiseandContext* MyLanguageParser::BitwiseandContext::bitwiseand() {
  return getRuleContext<MyLanguageParser::BitwiseandContext>(0);
}

tree::TerminalNode* MyLanguageParser::BitwiseandContext::BITAND() {
  return getToken(MyLanguageParser::BITAND, 0);
}


size_t MyLanguageParser::BitwiseandContext::getRuleIndex() const {
  return MyLanguageParser::RuleBitwiseand;
}


std::any MyLanguageParser::BitwiseandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitBitwiseand(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::BitwiseandContext* MyLanguageParser::bitwiseand() {
   return bitwiseand(0);
}

MyLanguageParser::BitwiseandContext* MyLanguageParser::bitwiseand(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::BitwiseandContext *_localctx = _tracker.createInstance<BitwiseandContext>(_ctx, parentState);
  MyLanguageParser::BitwiseandContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 28;
  enterRecursionRule(_localctx, 28, MyLanguageParser::RuleBitwiseand, precedence);

    

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
    setState(137);
    eqcomparison(0);
    _ctx->stop = _input->LT(-1);
    setState(144);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<BitwiseandContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBitwiseand);
        setState(139);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(140);
        match(MyLanguageParser::BITAND);
        setState(141);
        eqcomparison(0); 
      }
      setState(146);
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

//----------------- EqcomparisonContext ------------------------------------------------------------------

MyLanguageParser::EqcomparisonContext::EqcomparisonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::ComparisonContext* MyLanguageParser::EqcomparisonContext::comparison() {
  return getRuleContext<MyLanguageParser::ComparisonContext>(0);
}

MyLanguageParser::EqcomparisonContext* MyLanguageParser::EqcomparisonContext::eqcomparison() {
  return getRuleContext<MyLanguageParser::EqcomparisonContext>(0);
}

tree::TerminalNode* MyLanguageParser::EqcomparisonContext::EQUAL() {
  return getToken(MyLanguageParser::EQUAL, 0);
}

tree::TerminalNode* MyLanguageParser::EqcomparisonContext::NOTEQUAL() {
  return getToken(MyLanguageParser::NOTEQUAL, 0);
}


size_t MyLanguageParser::EqcomparisonContext::getRuleIndex() const {
  return MyLanguageParser::RuleEqcomparison;
}


std::any MyLanguageParser::EqcomparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitEqcomparison(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::EqcomparisonContext* MyLanguageParser::eqcomparison() {
   return eqcomparison(0);
}

MyLanguageParser::EqcomparisonContext* MyLanguageParser::eqcomparison(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::EqcomparisonContext *_localctx = _tracker.createInstance<EqcomparisonContext>(_ctx, parentState);
  MyLanguageParser::EqcomparisonContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 30;
  enterRecursionRule(_localctx, 30, MyLanguageParser::RuleEqcomparison, precedence);

    

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
    setState(148);
    comparison(0);
    _ctx->stop = _input->LT(-1);
    setState(158);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(156);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<EqcomparisonContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEqcomparison);
          setState(150);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(151);
          match(MyLanguageParser::EQUAL);
          setState(152);
          comparison(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<EqcomparisonContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEqcomparison);
          setState(153);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(154);
          match(MyLanguageParser::NOTEQUAL);
          setState(155);
          comparison(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(160);
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

//----------------- ComparisonContext ------------------------------------------------------------------

MyLanguageParser::ComparisonContext::ComparisonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::ShiftContext* MyLanguageParser::ComparisonContext::shift() {
  return getRuleContext<MyLanguageParser::ShiftContext>(0);
}

MyLanguageParser::ComparisonContext* MyLanguageParser::ComparisonContext::comparison() {
  return getRuleContext<MyLanguageParser::ComparisonContext>(0);
}

tree::TerminalNode* MyLanguageParser::ComparisonContext::LESS() {
  return getToken(MyLanguageParser::LESS, 0);
}

tree::TerminalNode* MyLanguageParser::ComparisonContext::LESSEQUAL() {
  return getToken(MyLanguageParser::LESSEQUAL, 0);
}

tree::TerminalNode* MyLanguageParser::ComparisonContext::GREATER() {
  return getToken(MyLanguageParser::GREATER, 0);
}

tree::TerminalNode* MyLanguageParser::ComparisonContext::GREATEREQUAL() {
  return getToken(MyLanguageParser::GREATEREQUAL, 0);
}


size_t MyLanguageParser::ComparisonContext::getRuleIndex() const {
  return MyLanguageParser::RuleComparison;
}


std::any MyLanguageParser::ComparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::ComparisonContext* MyLanguageParser::comparison() {
   return comparison(0);
}

MyLanguageParser::ComparisonContext* MyLanguageParser::comparison(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::ComparisonContext *_localctx = _tracker.createInstance<ComparisonContext>(_ctx, parentState);
  MyLanguageParser::ComparisonContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, MyLanguageParser::RuleComparison, precedence);

    

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
    setState(162);
    shift(0);
    _ctx->stop = _input->LT(-1);
    setState(178);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(176);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ComparisonContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleComparison);
          setState(164);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(165);
          match(MyLanguageParser::LESS);
          setState(166);
          shift(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ComparisonContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleComparison);
          setState(167);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(168);
          match(MyLanguageParser::LESSEQUAL);
          setState(169);
          shift(0);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ComparisonContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleComparison);
          setState(170);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(171);
          match(MyLanguageParser::GREATER);
          setState(172);
          shift(0);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ComparisonContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleComparison);
          setState(173);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(174);
          match(MyLanguageParser::GREATEREQUAL);
          setState(175);
          shift(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(180);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ShiftContext ------------------------------------------------------------------

MyLanguageParser::ShiftContext::ShiftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyLanguageParser::SummaContext* MyLanguageParser::ShiftContext::summa() {
  return getRuleContext<MyLanguageParser::SummaContext>(0);
}

MyLanguageParser::ShiftContext* MyLanguageParser::ShiftContext::shift() {
  return getRuleContext<MyLanguageParser::ShiftContext>(0);
}

tree::TerminalNode* MyLanguageParser::ShiftContext::SHIFTLEFT() {
  return getToken(MyLanguageParser::SHIFTLEFT, 0);
}

tree::TerminalNode* MyLanguageParser::ShiftContext::SHIFTRIGHT() {
  return getToken(MyLanguageParser::SHIFTRIGHT, 0);
}


size_t MyLanguageParser::ShiftContext::getRuleIndex() const {
  return MyLanguageParser::RuleShift;
}


std::any MyLanguageParser::ShiftContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyLanguageVisitor*>(visitor))
    return parserVisitor->visitShift(this);
  else
    return visitor->visitChildren(this);
}


MyLanguageParser::ShiftContext* MyLanguageParser::shift() {
   return shift(0);
}

MyLanguageParser::ShiftContext* MyLanguageParser::shift(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyLanguageParser::ShiftContext *_localctx = _tracker.createInstance<ShiftContext>(_ctx, parentState);
  MyLanguageParser::ShiftContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, MyLanguageParser::RuleShift, precedence);

    

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
    setState(182);
    summa(0);
    _ctx->stop = _input->LT(-1);
    setState(192);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(190);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ShiftContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift);
          setState(184);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(185);
          match(MyLanguageParser::SHIFTLEFT);
          setState(186);
          summa(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ShiftContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift);
          setState(187);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(188);
          match(MyLanguageParser::SHIFTRIGHT);
          setState(189);
          summa(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(194);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
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
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, MyLanguageParser::RuleSumma, precedence);

    

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
    setState(196);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(206);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(204);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SummaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSumma);
          setState(198);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(199);
          match(MyLanguageParser::PLUS);
          setState(200);
          term(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SummaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSumma);
          setState(201);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(202);
          match(MyLanguageParser::MINUS);
          setState(203);
          term(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(208);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
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

tree::TerminalNode* MyLanguageParser::TermContext::REM() {
  return getToken(MyLanguageParser::REM, 0);
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
  size_t startState = 38;
  enterRecursionRule(_localctx, 38, MyLanguageParser::RuleTerm, precedence);

    

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
    setState(210);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(223);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(221);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(212);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(213);
          match(MyLanguageParser::MULT);
          setState(214);
          factor();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(215);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(216);
          match(MyLanguageParser::DIV);
          setState(217);
          factor();
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(218);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(219);
          match(MyLanguageParser::REM);
          setState(220);
          factor();
          break;
        }

        default:
          break;
        } 
      }
      setState(225);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
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

tree::TerminalNode* MyLanguageParser::FactorContext::MINUS() {
  return getToken(MyLanguageParser::MINUS, 0);
}

MyLanguageParser::FactorContext* MyLanguageParser::FactorContext::factor() {
  return getRuleContext<MyLanguageParser::FactorContext>(0);
}

tree::TerminalNode* MyLanguageParser::FactorContext::BITNOT() {
  return getToken(MyLanguageParser::BITNOT, 0);
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
  enterRule(_localctx, 40, MyLanguageParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(236);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MyLanguageParser::MINUS: {
        enterOuterAlt(_localctx, 1);
        setState(226);
        match(MyLanguageParser::MINUS);
        setState(227);
        factor();
        break;
      }

      case MyLanguageParser::BITNOT: {
        enterOuterAlt(_localctx, 2);
        setState(228);
        match(MyLanguageParser::BITNOT);
        setState(229);
        factor();
        break;
      }

      case MyLanguageParser::NUMBER: {
        enterOuterAlt(_localctx, 3);
        setState(230);
        match(MyLanguageParser::NUMBER);
        break;
      }

      case MyLanguageParser::IDENT: {
        enterOuterAlt(_localctx, 4);
        setState(231);
        match(MyLanguageParser::IDENT);
        break;
      }

      case MyLanguageParser::LPAR: {
        enterOuterAlt(_localctx, 5);
        setState(232);
        match(MyLanguageParser::LPAR);
        setState(233);
        expr();
        setState(234);
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
    case 12: return bitwiseorSempred(antlrcpp::downCast<BitwiseorContext *>(context), predicateIndex);
    case 13: return bitwisexorSempred(antlrcpp::downCast<BitwisexorContext *>(context), predicateIndex);
    case 14: return bitwiseandSempred(antlrcpp::downCast<BitwiseandContext *>(context), predicateIndex);
    case 15: return eqcomparisonSempred(antlrcpp::downCast<EqcomparisonContext *>(context), predicateIndex);
    case 16: return comparisonSempred(antlrcpp::downCast<ComparisonContext *>(context), predicateIndex);
    case 17: return shiftSempred(antlrcpp::downCast<ShiftContext *>(context), predicateIndex);
    case 18: return summaSempred(antlrcpp::downCast<SummaContext *>(context), predicateIndex);
    case 19: return termSempred(antlrcpp::downCast<TermContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::bitwiseorSempred(BitwiseorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::bitwisexorSempred(BitwisexorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::bitwiseandSempred(BitwiseandContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::eqcomparisonSempred(EqcomparisonContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 3);
    case 4: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::comparisonSempred(ComparisonContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 5);
    case 6: return precpred(_ctx, 4);
    case 7: return precpred(_ctx, 3);
    case 8: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::shiftSempred(ShiftContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 9: return precpred(_ctx, 3);
    case 10: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::summaSempred(SummaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 11: return precpred(_ctx, 3);
    case 12: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool MyLanguageParser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return precpred(_ctx, 4);
    case 14: return precpred(_ctx, 3);
    case 15: return precpred(_ctx, 2);

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
