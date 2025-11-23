
// Generated from ./MyLanguage.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MyLanguageParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MyLanguageParser.
 */
class  MyLanguageVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MyLanguageParser.
   */
    virtual std::any visitProg(MyLanguageParser::ProgContext *context) = 0;

    virtual std::any visitTop_level(MyLanguageParser::Top_levelContext *context) = 0;

    virtual std::any visitFunc_decl(MyLanguageParser::Func_declContext *context) = 0;

    virtual std::any visitStmt(MyLanguageParser::StmtContext *context) = 0;

    virtual std::any visitStmts(MyLanguageParser::StmtsContext *context) = 0;

    virtual std::any visitIf_stmt(MyLanguageParser::If_stmtContext *context) = 0;

    virtual std::any visitWhile_stmt(MyLanguageParser::While_stmtContext *context) = 0;

    virtual std::any visitCall_stmt(MyLanguageParser::Call_stmtContext *context) = 0;

    virtual std::any visitVar_decl_stmt(MyLanguageParser::Var_decl_stmtContext *context) = 0;

    virtual std::any visitAssign_stmt(MyLanguageParser::Assign_stmtContext *context) = 0;

    virtual std::any visitPrint_stmt(MyLanguageParser::Print_stmtContext *context) = 0;

    virtual std::any visitExpr(MyLanguageParser::ExprContext *context) = 0;

    virtual std::any visitSumma(MyLanguageParser::SummaContext *context) = 0;

    virtual std::any visitTerm(MyLanguageParser::TermContext *context) = 0;

    virtual std::any visitFactor(MyLanguageParser::FactorContext *context) = 0;


};

