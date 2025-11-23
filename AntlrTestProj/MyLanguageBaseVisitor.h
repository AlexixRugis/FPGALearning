
// Generated from ./MyLanguage.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MyLanguageVisitor.h"


/**
 * This class provides an empty implementation of MyLanguageVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MyLanguageBaseVisitor : public MyLanguageVisitor {
public:

  virtual std::any visitProg(MyLanguageParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTop_level(MyLanguageParser::Top_levelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_decl(MyLanguageParser::Func_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(MyLanguageParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmts(MyLanguageParser::StmtsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_stmt(MyLanguageParser::If_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile_stmt(MyLanguageParser::While_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall_stmt(MyLanguageParser::Call_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar_decl_stmt(MyLanguageParser::Var_decl_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign_stmt(MyLanguageParser::Assign_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrint_stmt(MyLanguageParser::Print_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(MyLanguageParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSumma(MyLanguageParser::SummaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerm(MyLanguageParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactor(MyLanguageParser::FactorContext *ctx) override {
    return visitChildren(ctx);
  }


};

