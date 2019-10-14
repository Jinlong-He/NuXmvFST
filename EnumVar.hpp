//  EnumVar.hpp
//
//  Created by Jinlong He on 2018/7/6.
//  Copyright © 2018年 Jinlong He. All rights reserved.
//

#ifndef EnumVar_hpp 
#define EnumVar_hpp 
#include "Transition.hpp"

namespace nuxmvfst {

    /// \brief Enum Variables in NuXmv.
    class EnumVar : public Var {
    private:

        EnumVar() : Var() {
        }

        EnumVar(const Values& vs) : Var(vs) {
        }

        EnumVar(const Values& vs, Value* v) : Var(vs, v) {
        }

        EnumVar(ID i, const Values& vs) : Var(i, vs) {
        }

        EnumVar(const string& str, const Values& vs) : Var(str, vs) {
        }

        EnumVar(ID i, const Values& vs, Value* v) : Var(i, vs, v) {
        }

        EnumVar(const string& str, const Values& vs, Value* v) : Var(str, vs, v) {
        }
    public:
        ~EnumVar() {
            for (Transition* transition : transitions) {
                delete transition;
            }
        }

        Transition* mkTransition(Expression* expression, Var* var) {
            Transition* transition = new Transition(expression, var);
            transitions.push_back(transition);
            return transition;
        }

        Transition* mkTransition(Expression* expression, Value* value) {
            Transition* transition = new Transition(expression, value);
            transitions.push_back(transition);
            return transition;
        }

        string getVAR() {
            return name + " : " + getValuesStr();
        }

        string getASSIGN_INIT() {
            if (initValue) {
                return Init(name) + initValue -> getName() + ";\n";
            }
            return "";
        }

        string getASSIGN_NEXT() {
            if (transitions.size() == 0) return "";
            string res = Next(name);
            for (Transition* transition : transitions) {
                res += transition -> to_string();
            }
            return res + "esac;\n";
        }
    private:
        string List(const string& lhs, const string& rhs) {
            if (lhs.size() == 0) return rhs;
            if (rhs.size() == 0) return lhs;
            return lhs + " , " + rhs;
        }

        string Init(const string& str) {
            return "init(" + str + ") := ";
        }

        string Next(const string& str) {
            return "next(" + str + ") := case\n";
        }

        string getValuesStr() {
            string res = "";
            for (Value* value : values) {
                res = List(res, value -> getName());
            }
            return "{" + res + "};\n";
        }
        friend NuXmvFST;
    };

};

#endif /* EnumVar_hpp*/
