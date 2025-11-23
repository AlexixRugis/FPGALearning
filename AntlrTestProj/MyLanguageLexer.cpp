
// Generated from ./MyLanguage.g4 by ANTLR 4.13.2


#include "MyLanguageLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct MyLanguageLexerStaticData final {
  MyLanguageLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MyLanguageLexerStaticData(const MyLanguageLexerStaticData&) = delete;
  MyLanguageLexerStaticData(MyLanguageLexerStaticData&&) = delete;
  MyLanguageLexerStaticData& operator=(const MyLanguageLexerStaticData&) = delete;
  MyLanguageLexerStaticData& operator=(MyLanguageLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mylanguagelexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MyLanguageLexerStaticData> mylanguagelexerLexerStaticData = nullptr;

void mylanguagelexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mylanguagelexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(mylanguagelexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MyLanguageLexerStaticData>(
    std::vector<std::string>{
      "FUNC", "CALL", "VAR", "PRINT", "IF", "ELSE", "WHILE", "LBRA", "RBRA", 
      "LPAR", "RPAR", "PLUS", "MINUS", "MULT", "DIV", "REM", "LESS", "LESSEQUAL", 
      "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL", "ASSIGN", "SEMICOLON", 
      "IDENT", "NUMBER", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'func'", "'call'", "'var'", "'print'", "'if'", "'else'", "'while'", 
      "'{'", "'}'", "'('", "')'", "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", 
      "'<='", "'>'", "'>='", "'=='", "'!='", "'='", "';'"
    },
    std::vector<std::string>{
      "", "FUNC", "CALL", "VAR", "PRINT", "IF", "ELSE", "WHILE", "LBRA", 
      "RBRA", "LPAR", "RPAR", "PLUS", "MINUS", "MULT", "DIV", "REM", "LESS", 
      "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL", "ASSIGN", 
      "SEMICOLON", "IDENT", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,27,143,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,1,0,1,0,1,
  	0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,
  	1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,
  	9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,
  	1,16,1,17,1,17,1,17,1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,
  	1,21,1,22,1,22,1,23,1,23,1,24,1,24,5,24,130,8,24,10,24,12,24,133,9,24,
  	1,25,4,25,136,8,25,11,25,12,25,137,1,26,1,26,1,26,1,26,0,0,27,1,1,3,2,
  	5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,
  	16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,
  	1,0,4,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,1,0,48,57,3,
  	0,9,10,13,13,32,32,144,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,
  	0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,
  	1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,
  	0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,
  	0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,
  	1,0,0,0,0,53,1,0,0,0,1,55,1,0,0,0,3,60,1,0,0,0,5,65,1,0,0,0,7,69,1,0,
  	0,0,9,75,1,0,0,0,11,78,1,0,0,0,13,83,1,0,0,0,15,89,1,0,0,0,17,91,1,0,
  	0,0,19,93,1,0,0,0,21,95,1,0,0,0,23,97,1,0,0,0,25,99,1,0,0,0,27,101,1,
  	0,0,0,29,103,1,0,0,0,31,105,1,0,0,0,33,107,1,0,0,0,35,109,1,0,0,0,37,
  	112,1,0,0,0,39,114,1,0,0,0,41,117,1,0,0,0,43,120,1,0,0,0,45,123,1,0,0,
  	0,47,125,1,0,0,0,49,127,1,0,0,0,51,135,1,0,0,0,53,139,1,0,0,0,55,56,5,
  	102,0,0,56,57,5,117,0,0,57,58,5,110,0,0,58,59,5,99,0,0,59,2,1,0,0,0,60,
  	61,5,99,0,0,61,62,5,97,0,0,62,63,5,108,0,0,63,64,5,108,0,0,64,4,1,0,0,
  	0,65,66,5,118,0,0,66,67,5,97,0,0,67,68,5,114,0,0,68,6,1,0,0,0,69,70,5,
  	112,0,0,70,71,5,114,0,0,71,72,5,105,0,0,72,73,5,110,0,0,73,74,5,116,0,
  	0,74,8,1,0,0,0,75,76,5,105,0,0,76,77,5,102,0,0,77,10,1,0,0,0,78,79,5,
  	101,0,0,79,80,5,108,0,0,80,81,5,115,0,0,81,82,5,101,0,0,82,12,1,0,0,0,
  	83,84,5,119,0,0,84,85,5,104,0,0,85,86,5,105,0,0,86,87,5,108,0,0,87,88,
  	5,101,0,0,88,14,1,0,0,0,89,90,5,123,0,0,90,16,1,0,0,0,91,92,5,125,0,0,
  	92,18,1,0,0,0,93,94,5,40,0,0,94,20,1,0,0,0,95,96,5,41,0,0,96,22,1,0,0,
  	0,97,98,5,43,0,0,98,24,1,0,0,0,99,100,5,45,0,0,100,26,1,0,0,0,101,102,
  	5,42,0,0,102,28,1,0,0,0,103,104,5,47,0,0,104,30,1,0,0,0,105,106,5,37,
  	0,0,106,32,1,0,0,0,107,108,5,60,0,0,108,34,1,0,0,0,109,110,5,60,0,0,110,
  	111,5,61,0,0,111,36,1,0,0,0,112,113,5,62,0,0,113,38,1,0,0,0,114,115,5,
  	62,0,0,115,116,5,61,0,0,116,40,1,0,0,0,117,118,5,61,0,0,118,119,5,61,
  	0,0,119,42,1,0,0,0,120,121,5,33,0,0,121,122,5,61,0,0,122,44,1,0,0,0,123,
  	124,5,61,0,0,124,46,1,0,0,0,125,126,5,59,0,0,126,48,1,0,0,0,127,131,7,
  	0,0,0,128,130,7,1,0,0,129,128,1,0,0,0,130,133,1,0,0,0,131,129,1,0,0,0,
  	131,132,1,0,0,0,132,50,1,0,0,0,133,131,1,0,0,0,134,136,7,2,0,0,135,134,
  	1,0,0,0,136,137,1,0,0,0,137,135,1,0,0,0,137,138,1,0,0,0,138,52,1,0,0,
  	0,139,140,7,3,0,0,140,141,1,0,0,0,141,142,6,26,0,0,142,54,1,0,0,0,3,0,
  	131,137,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mylanguagelexerLexerStaticData = std::move(staticData);
}

}

MyLanguageLexer::MyLanguageLexer(CharStream *input) : Lexer(input) {
  MyLanguageLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *mylanguagelexerLexerStaticData->atn, mylanguagelexerLexerStaticData->decisionToDFA, mylanguagelexerLexerStaticData->sharedContextCache);
}

MyLanguageLexer::~MyLanguageLexer() {
  delete _interpreter;
}

std::string MyLanguageLexer::getGrammarFileName() const {
  return "MyLanguage.g4";
}

const std::vector<std::string>& MyLanguageLexer::getRuleNames() const {
  return mylanguagelexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& MyLanguageLexer::getChannelNames() const {
  return mylanguagelexerLexerStaticData->channelNames;
}

const std::vector<std::string>& MyLanguageLexer::getModeNames() const {
  return mylanguagelexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& MyLanguageLexer::getVocabulary() const {
  return mylanguagelexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MyLanguageLexer::getSerializedATN() const {
  return mylanguagelexerLexerStaticData->serializedATN;
}

const atn::ATN& MyLanguageLexer::getATN() const {
  return *mylanguagelexerLexerStaticData->atn;
}




void MyLanguageLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mylanguagelexerLexerInitialize();
#else
  ::antlr4::internal::call_once(mylanguagelexerLexerOnceFlag, mylanguagelexerLexerInitialize);
#endif
}
