//  Transition.hpp
//
//  Created by Jinlong He on 2018/7/6.
//  Copyright © 2018年 Jinlong He. All rights reserved.
//

#ifndef Transition_hpp 
#define Transition_hpp 
#include "Expression.hpp"

namespace nuxmvfst {
    /// /biref Transition in NuXmv.
    class Transition {
    private:
        Expression* expression;     ///< the expression for this Transition.
        Value* targetValue;         ///< the target Value for this Transition.
        Var* targetVar;             ///< the target Var for this Transition.

        /// \brief Default construction function.
        Transition() : expression(nullptr), targetValue(nullptr), targetVar(nullptr){}

        /// \brief Construction function with params.
        /// \param c The expression for this Transition.
        /// \param v The value for this Transition.
        Transition(Expression* exp, Value* v) : expression(exp), targetValue(v), targetVar(nullptr){}

        /// \brief Construction function with params.
        /// \param c The expression for this Transition.
        /// \param v The var for this Transition.
        Transition(Expression* exp, Var* v) : expression(exp), targetValue(nullptr), targetVar(v) {}

    public:
        /// \brief Desconstruction function.
        ~Transition() {
        }

        /// \brief Gets the expression for this Transition.
        /// \return Expression pointer.
        Expression* getExpression() {return expression;}
        Expression* getExpression() const {return expression;}

        /// \brief Gets the stateVar for this Transition.
        /// \return Var pointer.
        Var* getVar() {return targetVar;}
        Var* getVar() const {return targetVar;}

        /// \brief Gets the value for this Transition.
        /// \return Value pointer.
        Value* getValue() {return targetValue;}
        Value* getValue() const {return targetValue;}

        string to_string() {
            string expressionStr = "TRUE";
            if (expression) {
                expressionStr = expression -> to_string();
            }
            if (targetVar) {
                return expressionStr + " : " + targetVar -> getName() + ";\n";
            } else {
                return expressionStr + " : " + targetValue -> getName() + ";\n";
            }
        }

        friend NuXmvFST;
        friend EnumVar;
    };
};
#endif /* Transition_hpp */
