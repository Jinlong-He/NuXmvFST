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
        bool del;

        Expression() : leftExp(nullptr), rightExp(nullptr), del(0) {}

        Expression(Expression* exp) : leftExp(exp), rightExp(nullptr), del(0) {}

        Expression(Expression* l, Expression* r) : leftExp(l), rightExp(r), del(0) {}

    public:
        void mkLeftExp(Expression* exp) {
            leftExp = exp;
        }

        void mkRightExp(Expression* exp) {
            rightExp = exp;
        }

        virtual ~Expression() {
        }

        virtual string to_string() = 0;

    };

    /// \brief Disjunction Expresstion.
    class DisjunctionExp : public Expression {
    private:

        DisjunctionExp() : Expression() {}

        DisjunctionExp(Expression* exp) : Expression(exp) {}

        DisjunctionExp(Expression* l, Expression* r) : Expression(l, r) {}

        DisjunctionExp(Expressions& expressions) {
            create(expressions);
        }
    public:
        ~DisjunctionExp() {
            if (del) {
                delete leftExp;
                delete rightExp;
            }
        }

        string to_string() {
            if (!leftExp && !rightExp) return "";
            if (!leftExp) return rightExp -> to_string();
            if (!rightExp) return leftExp -> to_string();
            string leftStr = leftExp -> to_string();
            string rightStr = rightExp -> to_string();
            if (leftStr == "") return rightStr;
            if (rightStr == "") return leftStr;
            return leftStr + " | " + rightStr;
        }

        void create(Expressions& expressions) {
            ID size = expressions.size();
            if (size == 0) return;
            if (size == 2) {
                leftExp = new DisjunctionExp(expressions[0]);
                rightExp = new DisjunctionExp(expressions[1]);
            } else if (size == 1) {
                leftExp = new DisjunctionExp(expressions[0]);
            } else {
                del = 1;
                auto begin = expressions.begin();
                auto end = expressions.end();
                Expressions leftExpressions(begin, begin + size/2);
                Expressions rightExpressions(begin + size/2, end);
                leftExp = new DisjunctionExp(leftExpressions);
                rightExp = new DisjunctionExp(rightExpressions);
            }
        }

        friend NuXmvFST;
    };

    /// \brief Conjuntion Expresstion.
    class ConjunctionExp : public Expression {
    private:
        ConjunctionExp() : Expression() {}

        ConjunctionExp(Expression* exp) : Expression(exp) {}

        ConjunctionExp(Expression* l, Expression* r) : Expression(l, r) {}

        ConjunctionExp(Expressions& expressions) {
            create(expressions);
        }
    public:
        ~ConjunctionExp() {}

        string to_string() {
            if (!leftExp && !rightExp) return "";
            if (!leftExp) return rightExp -> to_string();
            if (!rightExp) return leftExp -> to_string();
            string leftStr = leftExp -> to_string();
            string rightStr = rightExp -> to_string();
            if (leftStr == "") return rightStr;
            if (rightStr == "") return leftStr;
            return "(" + leftStr + ") & (" + rightStr + ")";
        }

        void create(Expressions& expressions) {
            ID size = expressions.size();
            if (size == 0) return;
            if (size == 2) {
                leftExp = new ConjunctionExp(expressions[0]);
                rightExp = new ConjunctionExp(expressions[1]);
            } else if (size == 1) {
                leftExp = new ConjunctionExp(expressions[0]);
            } else {
                del = 1;
                auto begin = expressions.begin();
                auto end = expressions.end();
                Expressions leftExpressions(begin, begin + size/2);
                Expressions rightExpressions(begin + size/2, end);
                leftExp = new ConjunctionExp(leftExpressions);
                rightExp = new ConjunctionExp(rightExpressions);
            }
        }
        friend NuXmvFST;
    };
};
#endif /* Expression_hpp*/
