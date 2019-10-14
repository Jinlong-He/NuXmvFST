//  Alias.hpp
//
//  Created by Jinlong He on 2018/7/6.
//  Copyright © 2018年 Jinlong He. All rights reserved.
//

#ifndef NuXmvFSTAlias_hpp
#define NuXmvFSTAlias_hpp

#include <climits>
#include <math.h>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <regex>
#include <string>
#include <vector>
#include <tuple>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "../Utility/Utility.hpp"
using namespace utility;

using namespace std;
namespace nuxmvfst {

    class Var;
    class EnumVar;
    class Value;
    class Atomic;
    class EquAtomic;
    class Expression;
    class ConjunctionExp;
    class DisjunctionExp;
    class Transition;
    class NuXmvFST;

    typedef vector<Value*> Values;
    typedef vector<Value*> Path;
    typedef vector<Var*> Vars;
    typedef vector<Atomic*> Atomics;
    typedef vector<Transition*> Transitions;
    typedef vector<Transition*> Transitions;
    typedef vector<Expression*> Expressions;
    typedef size_t ID;
    
}
#endif /* NuXmvFSTAlias_hpp */
