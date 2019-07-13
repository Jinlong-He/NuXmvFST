//  Expression.hpp
//
//  Created by Jinlong He on 2018/7/6.
//  Copyright © 2018年 Jinlong He. All rights reserved.
//

#ifndef Expression_hpp 
#define Expression_hpp
#include "Var.hpp"
#include "Value.hpp"

namespace nuxmvfst {
    /// \brief Expression.
    class Expression {
    protected:
        Expression* leftExp;
        Expression* rightExp;
    public:
        Expression() : leftExp(nullptr), rightExp(nullptr) {}

        Expression(Expression* exp) : leftExp(exp), rightExp(nullptr) {}

        Expression(Expression* l, Expression* r) : leftExp(l), rightExp(r) {}

        void mkLeftExp(Expression* exp) {
            leftExp = exp;
        }

        void mkRightExp(Expression* exp) {
            rightExp = exp;
        }

        virtual ~Expression() {
        }

        virtual string getStr() = 0;

    };

    /// \brief Disjunction Expresstion.
    class DisjunctionExp : public Expression {
    public:
        DisjunctionExp() : Expression() {}

        DisjunctionExp(Expression* exp) : Expression(exp) {}

        DisjunctionExp(Expression* l, Expression* r) : Expression(l, r) {}

        ~DisjunctionExp() {
        }

        string getStr() {
            if (!leftExp && !rightExp) return "";
            if (!leftExp) return rightExp -> getStr();
            if (!rightExp) return leftExp -> getStr();
            string leftStr = leftExp -> getStr();
            string rightStr = rightExp -> getStr();
            if (leftStr == "") return rightStr;
            if (rightStr == "") return leftStr;
            return leftStr + " | " + rightStr;
        }
    };

    /// \brief Conjuntion Expresstion.
    class ConjunctionExp : public Expression {
    public:
        ConjunctionExp() : Expression() {}

        ConjunctionExp(Expression* exp) : Expression(exp) {}

        ConjunctionExp(Expression* l, Expression* r) : Expression(l, r) {}

        ~ConjunctionExp() {}

        string getStr() {
            if (!leftExp && !rightExp) return "";
            if (!leftExp) return rightExp -> getStr();
            if (!rightExp) return leftExp -> getStr();
            string leftStr = leftExp -> getStr();
            string rightStr = rightExp -> getStr();
            if (leftStr == "") return rightStr;
            if (rightStr == "") return leftStr;
            return "(" + leftStr + ") & (" + rightStr + ")";
        }
    };
};
#endif /* Expression_hpp*/
