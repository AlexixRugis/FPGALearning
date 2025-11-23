#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <optional>
#include <tuple>
#include <any>

#include "antlr4-runtime.h"
#include "MyLanguageBaseVisitor.h"
#include "Types.h"
#include "VariableAllocator.h"
#include "CodeGenerator.h"
#include "LabelGenerator.h"

class MyVisitor final : public MyLanguageBaseVisitor
{
private:
    std::vector<Compiler::VariableAllocator> mAllocators;
    Compiler::CodeGenerator mCodeGen;
    Compiler::LabelGenerator mLabelGenerator;
    int mIndent = 0;

    void tab() const
    {
        for (int i = 0; i < mIndent; i++) std::cout << "  ";
    }

    std::optional<std::pair<Compiler::addr_t, Compiler::VariableAllocator::Scope>> getDeclaration(const std::string& varName) const
    {
        for (auto iter = mAllocators.rbegin(); iter != mAllocators.rend(); ++iter)
        {
            auto addr = iter->getAddr(varName);
            if (addr.has_value())
            {
                return std::make_pair(addr.value(), iter->getScope());
            }
        }

        return std::nullopt;
    }

    bool isDeclared(const std::string& varName) const
    {
        return getDeclaration(varName).has_value();
    }

public:
    using program_t = std::tuple<std::vector<Compiler::Assembler::opcode_t>, std::vector<std::pair<std::string, size_t>>>;

    MyVisitor()
    {
        mAllocators.emplace_back(200, Compiler::VariableAllocator::GLOBAL);
    }

    program_t visitAll(MyLanguageParser::ProgContext* ctx)
    {
        visitProg(ctx);

        mCodeGen.resolveRefs();

        return { mCodeGen.getProgram(), mCodeGen.getLabels() };
    }

    std::any visitProg(MyLanguageParser::ProgContext* ctx) override
    {
        tab(); std::cout << "Program\n";
        mIndent++;

        mCodeGen.compileConst(1024);
        mCodeGen.compileLoadFp();

        for (auto child : ctx->top_level())
        {
            if (auto varDecl = child->var_decl_stmt())
            {
                visitVar_decl_stmt(varDecl);
            }
        }

        mCodeGen.compileRef("main");
        mCodeGen.compileAJmp();
        auto endLoop = mLabelGenerator.next();
        mCodeGen.declareLabel(endLoop);
        mCodeGen.compileRef(endLoop);
        mCodeGen.compileAJmp();

        for (auto child : ctx->top_level())
        {
            if (auto funcDecl = child->func_decl())
            {
                visitFunc_decl(funcDecl);
            }
        }

        mIndent--;

        return {};
    }

    std::any visitTop_level(MyLanguageParser::Top_levelContext* ctx) override
    {
        return visitChildren(ctx);
    }

    std::any visitFunc_decl(MyLanguageParser::Func_declContext* ctx) override
    {
        mIndent++;
        std::cout << "FUNC " << ctx->IDENT()->getText() << '\n';
        mCodeGen.declareLabel(ctx->IDENT()->getText());
        mAllocators.emplace_back(0, Compiler::VariableAllocator::STACK);

        mCodeGen.compilePrologue();
        visitStmts(ctx->stmts());
        mCodeGen.compileEpilogue(mAllocators.back().getMaxAlloc());

        mAllocators.pop_back();

        mIndent--;

        return {};
    }

    std::any visitCall_stmt(MyLanguageParser::Call_stmtContext* ctx) override
    {
        mIndent++;
        std::cout << "CALL " << ctx->IDENT()->getText() << '\n';
        mIndent--;

        mCodeGen.compileRef(ctx->IDENT()->getText());
        mCodeGen.compileAJmp();

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
        mAllocators.back().startBlock();

        auto elseBegin = mLabelGenerator.next();

        tab(); std::cout << "IfStmt\n";
        mIndent++;

        tab(); std::cout << "Condition:\n";
        mIndent++;
        visit(ctx->expr());
        mCodeGen.compileRef(elseBegin);
        mCodeGen.compileCJmpz();
        mIndent--;

        mAllocators.back().startBlock();
        tab(); std::cout << "Then:\n";
        mIndent++;
        visit(ctx->stmt(0));
        mIndent--;
        mAllocators.back().endBlock();

        if (ctx->ELSE())
        {
            auto operatorEnd = mLabelGenerator.next();
            mCodeGen.compileRef(operatorEnd);
            mCodeGen.compileAJmp();

            mCodeGen.declareLabel(elseBegin);

            mAllocators.back().startBlock();
            tab(); std::cout << "Else:\n";
            mIndent++;
            visit(ctx->stmt(1));
            mIndent--;
            mAllocators.back().endBlock();

            mCodeGen.declareLabel(operatorEnd);
        }
        else
        {
            mCodeGen.declareLabel(elseBegin);
        }
        
        mIndent--;
        mAllocators.back().endBlock();

        return {};
    }

    std::any visitWhile_stmt(MyLanguageParser::While_stmtContext* ctx) override
    {
        mAllocators.back().startBlock();

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

        mAllocators.back().startBlock();
        tab(); std::cout << "Body:\n";
        mIndent++;
        visit(ctx->stmt());
        mIndent--;
        mAllocators.back().endBlock();

        mCodeGen.compileRef(loop);
        mCodeGen.compileAJmp();

        mCodeGen.declareLabel(loopEnd);

        mIndent--;
        mAllocators.back().endBlock();
        return {};
    }

    std::any visitVar_decl_stmt(MyLanguageParser::Var_decl_stmtContext* ctx) override
    {
        Compiler::addr_t addr = mAllocators.back().alloc(ctx->IDENT()->getText());

        tab(); std::cout << "VarDecl: " << ctx->IDENT()->getText() << "\n";
        mIndent++;
        tab(); std::cout << "Value:\n";
        mIndent++;
        visit(ctx->expr());
        mIndent -= 2;
        
        if (mAllocators.back().getScope() == Compiler::VariableAllocator::GLOBAL)
        {
            mCodeGen.compileSave(addr);
        }
        else
        {
            mCodeGen.compileStackSave(addr);
        }

        return {};
    }

    std::any visitAssign_stmt(MyLanguageParser::Assign_stmtContext* ctx) override
    {
        auto decl = getDeclaration(ctx->IDENT()->getText());

        if (!decl.has_value())
        {
            throw std::runtime_error(__FUNCTION__ ": variable \'" + ctx->IDENT()->getText() + "\' is not declared.");
        }

        tab(); std::cout << "Assign: " << ctx->IDENT()->getText() << "\n";
        mIndent++;
        visit(ctx->expr());
        mIndent--;

        if (decl.value().second == Compiler::VariableAllocator::GLOBAL)
        {
            mCodeGen.compileSave(decl.value().first);
        }
        else
        {
            mCodeGen.compileStackSave(decl.value().first);
        }

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
            auto decl = getDeclaration(ctx->IDENT()->getText());

            if (!decl.has_value())
            {
                throw std::runtime_error(__FUNCTION__ ": variable \'" + ctx->IDENT()->getText() + "\' is not declared.");
            }

            tab(); std::cout << "Ident: " << ctx->IDENT()->getText() << "\n";

            if (decl.value().second == Compiler::VariableAllocator::GLOBAL)
            {
                mCodeGen.compileLoad(decl.value().first);
            }
            else
            {
                mCodeGen.compileStackLoad(decl.value().first);
            }
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
