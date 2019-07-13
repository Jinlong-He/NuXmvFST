//  NuXmvFST.hpp
//
//  Created by Jinlong He on 2018/7/6.
//  Copyright © 2018年 Jinlong He. All rights reserved.
//

#ifndef NuXmv_hpp
#define NuXmv_hpp
#include "EnumVar.hpp"
#include "Atomic.hpp"

namespace nuxmvfst {
    /// \brief A class for transfering to NuXmv.
    ///
    /// Examples:
    /// NuXmv solver;
    /// EnumValue* v1 = solver.mkEnumValue();
    /// EnumValue* v2 = solver.mkEnumValue();
    /// Values values;
    /// values.push_back(v1);
    /// values.push_back(v2);
    /// EnumVar* s1 = solver.mkEnumVar(values, v1);
    /// EnumVar* s2 = solver.mkEnumVar(values, v1);
    /// EnumVar* c = solver.mkEnumVar(values);
    /// Condition* condition = solver.mkCondition();
    /// Condition* tarConfig = solver.mkTargetConfig();
    /// Conjunction* conjunction = condition -> mkConjunction();
    /// Conjunction* tConjunction = tarConfig -> mkConjunction();
    /// conjunction -> mkEquAtomic(s1, v1);
    /// conjunction -> mkEquAtomic(s2, v2, 0);
    /// tConjunction -> mkEquAtomic(s1, v2);
    /// s1 -> mkTransition(condition, v2);
    /// s1 -> mkTransition(nullptr, v1);
    /// cout << solver.getSMV() << endl;
    class NuXmvFST {
    protected:
        Vars vars;                      ///< the Vars for this NuXmvFST.
        Values values;                  ///< the whole values for this NuXmvFST.
        Expression* targetConfig;       ///< the vefication configuration for this NuXmvFST.
        Expressions expressions;        ///< the Expressions made in this NuXmvFST.

    public:
        /// \brief Default construction function.
        NuXmvFST() : targetConfig(nullptr) {
        }

        /// \brief Desconstruction function.
        ~NuXmvFST() {
            for (Var* var: vars) {
                delete var;
            }
            for (Value* value : values) {
                delete value;
            }
            for (Expression* exp: expressions) {
                delete exp;
            }
        }

        /// \brief Gets Vars for this NuXmv.
        /// \return reference of Vars.
        Vars& getVars() {
            return vars;
        }

        const Vars& getVars() const {
            return vars;
        }

        /// \brief Gets Values for this NuXmv.
        /// \return reference of Values.
        Values& getValues() {
            return values;
        }

        const Values& getValues() const {
            return values;
        }

        /// \brief Makes a EnumVar for this NuXmv.
        /// \param vs The available values for this Var.
        EnumVar* mkEnumVar(const Values& vs) {
            EnumVar* var = new EnumVar(vs);
            vars.push_back(var);
            return var;
        }

        /// \brief Makes a EnumVar for this NuXmv.
        /// \param vs The available values for this Var.
        /// \param v The initial value for this Var.
        EnumVar* mkEnumVar(const Values& vs, Value* v) {
            EnumVar* var = new EnumVar(vs, v);
            vars.push_back(var);
            return var;
        }

        /// \brief Makes a EnumVar for this NuXmv.
        /// \param i The id for this Var.
        /// \param vs The available values for this Var.
        EnumVar* mkEnumVar(ID i, const Values& vs) {
            EnumVar* var = new EnumVar(i, vs);
            vars.push_back(var);
            return var;
        }

        /// \brief Makes a EnumVar for this NuXmv.
        /// \param str The name for this Var.
        /// \param vs The available values for this Var.
        EnumVar* mkEnumVar(const string& str, const Values& vs) {
            EnumVar* var = new EnumVar(str, vs);
            vars.push_back(var);
            return var;
        }

        /// \brief Makes a EnumVar for this NuXmv.
        /// \param i The id for this Var.
        /// \param vs The available values for this Var.
        /// \param v The initial value for this Var.
        EnumVar* mkEnumVar(ID i, const Values& vs, Value* v) {
            EnumVar* var = new EnumVar(i, vs, v);
            vars.push_back(var);
            return var;
        }

        /// \brief Makes a EnumVar for this NuXmv.
        /// \param str The name for this Var.
        /// \param vs The available values for this Var.
        /// \param v The initial value for this Var.
        EnumVar* mkEnumVar(const string& str, const Values& vs, Value* v) {
            EnumVar* var = new EnumVar(str, vs, v);
            vars.push_back(var);
            return var;
        }

        /// \brief Makes a Value for this NuXmv.
        /// \return Value pointer.
        EnumValue* mkEnumValue() {
            EnumValue* value = new EnumValue();
            values.push_back(value);
            return value;
        }

        /// \brief Makes a Value for this NuXmv.
        /// \param id Id for this Value.
        /// \return Value pointer.
        EnumValue* mkEnumValue(ID id) {
            EnumValue* value = new EnumValue(id);
            values.push_back(value);
            return value;
        }

        /// \brief Makes a Value for this NuXmv.
        /// \param str Name for this Value.
        /// \return Value pointer.
        EnumValue* mkEnumValue(const string& str) {
            EnumValue* value = new EnumValue(str);
            values.push_back(value);
            return value;
        }

        /// \brief Makes a EquAtomic for this Disjunction.
        /// \param lVar lhs Var for this Atomic.
        /// \param rValue rhs Value for this Atomic.
        /// \param f Flag for this Atomic. Default is true.
        EquAtomic* mkEquAtomic(Var* lVar, Value* rValue, bool f = true) {
            EquAtomic* atomic = new EquAtomic(lVar, rValue, f);
            expressions.push_back(atomic);
            return atomic;
        }

        /// \brief Makes a Conjunction Expression uesd in Transition for this NuXmv.
        /// \return Pointer of ConjunctionExp.
        ConjunctionExp* mkConjunctionExp() {
            ConjunctionExp* exp = new ConjunctionExp();
            expressions.push_back(exp);
            return exp;
        }

        ConjunctionExp* mkConjunctionExp(Expression* e) {
            ConjunctionExp* exp = new ConjunctionExp(e);
            expressions.push_back(exp);
            return exp;
        }

        ConjunctionExp* mkConjunctionExp(Expression* l, Expression* r) {
            ConjunctionExp* exp = new ConjunctionExp(l, r);
            expressions.push_back(exp);
            return exp;
        }
        /// \brief Makes a Disjunction Expression uesd in Transition for this NuXmv.
        /// \return Pointer of DisjunctionExp.
        DisjunctionExp* mkDisjunctionExp() {
            DisjunctionExp* exp = new DisjunctionExp();
            expressions.push_back(exp);
            return exp;
        }

        DisjunctionExp* mkDisjunctionExp(Expression* e) {
            DisjunctionExp* exp = new DisjunctionExp(e);
            expressions.push_back(exp);
            return exp;
        }

        DisjunctionExp* mkDisjunctionExp(Expression* l, Expression* r) {
            DisjunctionExp* exp = new DisjunctionExp(l, r);
            expressions.push_back(exp);
            return exp;
        }
        /// \brief Makes target configuration for this NuXmv.
        /// \return Condition pointer.
        Expression* mkTargetConfig() {
            targetConfig = mkConjunctionExp();
            return targetConfig;
        }

        /// \brief Gets the VAR part for this NuXmv.
        /// \return string.
        string getVAR() {
            string res = "VAR\n";
            for (Var* var: vars) {
                res += var -> getVAR();
            }
            return res;
        }

        /// \brief Gets the INIT part for this NuXmv.
        /// \return string.
        string getASSIGN_INIT() {
            string res = "ASSIGN\n";
            for (Var* var: vars) {
                res += var -> getASSIGN_INIT();
            }
            return res;
        }

        /// \brief Gets the NEXT part for this NuXmv.
        /// \return string.
        string getASSIGN_NEXT() {
            string res = "";
            for (Var* var: vars) {
                res += var -> getASSIGN_NEXT();
            }
            return res;
        }

        /// \brief Gets the INVARSPEC part for this NuXmv.
        /// \return string.
        string getINVARSPEC() {
            string targetConfigStr = "TRUE";
            if (targetConfig) targetConfigStr = targetConfig -> getStr();
            return "INVARSPEC\n!(" + targetConfigStr + ");";
        }

        /// \brief Gets the VAR and ASSIGN parts for this NuXmv.
        /// \return string.
        string getPreSMV() {
            return getVAR() + getASSIGN_INIT() + getASSIGN_NEXT();
        }

        /// \brief Gets the SMV for this NuXmv.
        /// \return string.
        string getSMV() {
            return getVAR() + getASSIGN_INIT() + getASSIGN_NEXT() + getINVARSPEC();
        }
    };
};


#endif /* NuXmv_hpp */
