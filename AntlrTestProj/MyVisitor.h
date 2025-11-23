#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include "antlr4-runtime.h"
#include "MyLanguageBaseVisitor.h"
#include "Types.h"
#include "VariableAllocator.h"
#include "CodeGenerator.h"
#include "LabelGenerator.h"

class MyVisitor final : public MyLanguageBaseVisitor
{
private:
    Compiler::VariableAllocator mAllocator;
    Compiler::CodeGenerator mCodeGen;
    Compiler::LabelGenerator mLabelGenerator;
    int mIndent = 0;

    void tab() const
    {
        for (int i = 0; i < mIndent; i++) std::cout << "  ";
    }

    bool isDeclared(const Compiler::ident_t& name)
    {
        return mAllocator.getAddr(name).has_value();
    }

public:
    MyVisitor() : mAllocator(200) {}

    std::vector<Compiler::Assembler::opcode_t> visitAll(MyLanguageParser::ProgContext* ctx)
    {
        visitProg(ctx);
        
        auto endLoop = mLabelGenerator.next();
        mCodeGen.declareLabel(endLoop);
        mCodeGen.compileRef(endLoop);
        mCodeGen.compileAJmp();

        mCodeGen.resolveRefs();

        return mCodeGen.getProgram();
    }

    std::any visitProg(MyLanguageParser::ProgContext* ctx) override
    {
        tab(); std::cout << "Program\n";
        mIndent++;
        visitChildren(ctx);
        mIndent--;
        return {};
    }

    std::any visitStmts(MyLanguageParser::StmtsContext* ctx) override
    {
        for (auto s : ctx->stmt())
            visit(s);
        return {};
    }

    std::any visitStmt(MyLanguageParser::StmtContext* ctx) override
    {
        return visitChildren(ctx);
    }

    std::any visitIf_stmt(MyLanguageParser::If_stmtContext* ctx) override
    {
        mAllocator.startBlock();

        auto elseBegin = mLabelGenerator.next();

        tab(); std::cout << "IfStmt\n";
        mIndent++;

        tab(); std::cout << "Condition:\n";
        mIndent++;
        visit(ctx->expr());
        mCodeGen.compileRef(elseBegin);
        mCodeGen.compileCJmpz();
        mIndent--;

        mAllocator.startBlock();
        tab(); std::cout << "Then:\n";
        mIndent++;
        visit(ctx->stmt(0));
        mIndent--;
        mAllocator.endBlock();

        if (ctx->ELSE())
        {
            auto operatorEnd = mLabelGenerator.next();
            mCodeGen.compileRef(operatorEnd);
            mCodeGen.compileAJmp();

            mCodeGen.declareLabel(elseBegin);

            mAllocator.startBlock();
            tab(); std::cout << "Else:\n";
            mIndent++;
            visit(ctx->stmt(1));
            mIndent--;
            mAllocator.endBlock();

            mCodeGen.declareLabel(operatorEnd);
        }
        else
        {
            mCodeGen.declareLabel(elseBegin);
        }
        
        mIndent--;
        mAllocator.endBlock();

        return {};
    }

    std::any visitWhile_stmt(MyLanguageParser::While_stmtContext* ctx) override
    {
        mAllocator.startBlock();

        tab(); std::cout << "WhileStmt\n";
        mIndent++;

        auto loop = mLabelGenerator.next();
        mCodeGen.declareLabel(loop);

        tab(); std::cout << "Condition:\n";
        mIndent++;
        visit(ctx->expr());

        auto loopEnd = mLabelGenerator.next();
        mCodeGen.compileRef(loopEnd);
        mCodeGen.compileCJmpz();

        mIndent--;

        mAllocator.startBlock();
        tab(); std::cout << "Body:\n";
        mIndent++;
        visit(ctx->stmt());
        mIndent--;
        mAllocator.endBlock();

        mCodeGen.compileRef(loop);
        mCodeGen.compileAJmp();

        mCodeGen.declareLabel(loopEnd);

        mIndent--;
        mAllocator.endBlock();
        return {};
    }

    std::any visitVar_decl_stmt(MyLanguageParser::Var_decl_stmtContext* ctx) override
    {
        Compiler::addr_t addr = mAllocator.alloc(ctx->IDENT()->getText());

        tab(); std::cout << "VarDecl: " << ctx->IDENT()->getText() << "\n";
        mIndent++;
        tab(); std::cout << "Value:\n";
        mIndent++;
        visit(ctx->expr());
        mIndent -= 2;

        mCodeGen.compileSave(addr);

        return {};
    }

    std::any visitAssign_stmt(MyLanguageParser::Assign_stmtContext* ctx) override
    {
        if (!isDeclared(ctx->IDENT()->getText()))
        {
            throw std::runtime_error(__FUNCTION__ ": variable \'" + ctx->IDENT()->getText() + "\' is not declared.");
        }

        tab(); std::cout << "Assign: " << ctx->IDENT()->getText() << "\n";
        mIndent++;
        visit(ctx->expr());
        mIndent--;

        mCodeGen.compileSave(mAllocator.getAddr(ctx->IDENT()->getText()).value());

        return {};
    }

    std::any visitPrint_stmt(MyLanguageParser::Print_stmtContext* ctx) override
    {
        tab(); std::cout << "Print\n";
        mIndent++;
        visit(ctx->expr());
        mIndent--;

        mCodeGen.compileSave(1u << 30);

        return {};
    }

    std::any visitExpr(MyLanguageParser::ExprContext* ctx) override
    {
        if (ctx->LESS())
        {
            tab(); std::cout << "< (LessExpr)\n";
            mIndent++;
            visit(ctx->summa(0));
            visit(ctx->summa(1));
            mIndent--;

            mCodeGen.compileLt();

            return {};
        }

        return visitChildren(ctx); // просто сумма
    }

    std::any visitSumma(MyLanguageParser::SummaContext* ctx) override
    {
        if (ctx->PLUS())
        {
            tab(); std::cout << "+ (Add)\n";
            mIndent++;
            visit(ctx->summa());
            visit(ctx->term());
            mIndent--;

            mCodeGen.compileAdd();

            return {};
        } else if (ctx->MINUS())
        {
            tab(); std::cout << "- (Sub)\n";
            mIndent++;
            visit(ctx->summa());
            visit(ctx->term());
            mIndent--;

            mCodeGen.compileSub();

            return {};
        }

        return visit(ctx->term());
    }

    std::any visitTerm(MyLanguageParser::TermContext* ctx) override
    {
        if (ctx->MULT())
        {
            tab(); std::cout << "* (Mul)\n";
            mIndent++;
            visit(ctx->term());
            visit(ctx->factor());
            mIndent--;

            mCodeGen.compileMul();

            return {};
        } else if (ctx->DIV())
        {
            tab(); std::cout << "/ (Div)\n";
            mIndent++;
            visit(ctx->term());
            visit(ctx->factor());
            mIndent--;

            mCodeGen.compileDiv();

            return {};
        }

        return visit(ctx->factor());
    }

    std::any visitFactor(MyLanguageParser::FactorContext* ctx) override
    {
        if (ctx->NUMBER())
        {
            tab(); std::cout << "Number: " << ctx->NUMBER()->getText() << "\n";

            mCodeGen.compileConst(stoul(ctx->NUMBER()->getText()));
        } else if (ctx->IDENT())
        {
            if (!isDeclared(ctx->IDENT()->getText()))
            {
                throw std::runtime_error(__FUNCTION__ ": variable \'" + ctx->IDENT()->getText() + "\' is not declared.");
            }

            tab(); std::cout << "Ident: " << ctx->IDENT()->getText() << "\n";

            mCodeGen.compileLoad(mAllocator.getAddr(ctx->IDENT()->getText()).value());
        } else
        {
            tab(); std::cout << "Paren\n";
            mIndent++;
            visit(ctx->expr());
            mIndent--;
        }
        return {};
    }
};
