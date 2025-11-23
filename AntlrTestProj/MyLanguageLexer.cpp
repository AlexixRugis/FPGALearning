
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
      "LPAR", "RPAR", "PLUS", "MINUS", "MULT", "DIV", "LESS", "ASSIGN", 
      "SEMICOLON", "IDENT", "NUMBER", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,21,115,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,
  	1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,
  	1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,
  	1,15,1,16,1,16,1,17,1,17,1,18,1,18,5,18,102,8,18,10,18,12,18,105,9,18,
  	1,19,4,19,108,8,19,11,19,12,19,109,1,20,1,20,1,20,1,20,0,0,21,1,1,3,2,
  	5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,
  	16,33,17,35,18,37,19,39,20,41,21,1,0,4,3,0,65,90,95,95,97,122,4,0,48,
  	57,65,90,95,95,97,122,1,0,48,57,3,0,9,10,13,13,32,32,116,0,1,1,0,0,0,
  	0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,
  	0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,
  	0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,
  	1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,1,43,1,0,0,0,3,48,1,0,
  	0,0,5,53,1,0,0,0,7,57,1,0,0,0,9,63,1,0,0,0,11,66,1,0,0,0,13,71,1,0,0,
  	0,15,77,1,0,0,0,17,79,1,0,0,0,19,81,1,0,0,0,21,83,1,0,0,0,23,85,1,0,0,
  	0,25,87,1,0,0,0,27,89,1,0,0,0,29,91,1,0,0,0,31,93,1,0,0,0,33,95,1,0,0,
  	0,35,97,1,0,0,0,37,99,1,0,0,0,39,107,1,0,0,0,41,111,1,0,0,0,43,44,5,102,
  	0,0,44,45,5,117,0,0,45,46,5,110,0,0,46,47,5,99,0,0,47,2,1,0,0,0,48,49,
  	5,99,0,0,49,50,5,97,0,0,50,51,5,108,0,0,51,52,5,108,0,0,52,4,1,0,0,0,
  	53,54,5,118,0,0,54,55,5,97,0,0,55,56,5,114,0,0,56,6,1,0,0,0,57,58,5,112,
  	0,0,58,59,5,114,0,0,59,60,5,105,0,0,60,61,5,110,0,0,61,62,5,116,0,0,62,
  	8,1,0,0,0,63,64,5,105,0,0,64,65,5,102,0,0,65,10,1,0,0,0,66,67,5,101,0,
  	0,67,68,5,108,0,0,68,69,5,115,0,0,69,70,5,101,0,0,70,12,1,0,0,0,71,72,
  	5,119,0,0,72,73,5,104,0,0,73,74,5,105,0,0,74,75,5,108,0,0,75,76,5,101,
  	0,0,76,14,1,0,0,0,77,78,5,123,0,0,78,16,1,0,0,0,79,80,5,125,0,0,80,18,
  	1,0,0,0,81,82,5,40,0,0,82,20,1,0,0,0,83,84,5,41,0,0,84,22,1,0,0,0,85,
  	86,5,43,0,0,86,24,1,0,0,0,87,88,5,45,0,0,88,26,1,0,0,0,89,90,5,42,0,0,
  	90,28,1,0,0,0,91,92,5,47,0,0,92,30,1,0,0,0,93,94,5,60,0,0,94,32,1,0,0,
  	0,95,96,5,61,0,0,96,34,1,0,0,0,97,98,5,59,0,0,98,36,1,0,0,0,99,103,7,
  	0,0,0,100,102,7,1,0,0,101,100,1,0,0,0,102,105,1,0,0,0,103,101,1,0,0,0,
  	103,104,1,0,0,0,104,38,1,0,0,0,105,103,1,0,0,0,106,108,7,2,0,0,107,106,
  	1,0,0,0,108,109,1,0,0,0,109,107,1,0,0,0,109,110,1,0,0,0,110,40,1,0,0,
  	0,111,112,7,3,0,0,112,113,1,0,0,0,113,114,6,20,0,0,114,42,1,0,0,0,3,0,
  	103,109,1,6,0,0
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
