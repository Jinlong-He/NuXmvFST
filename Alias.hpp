//  Alias.hpp
//
//  Created by Jinlong He on 2018/7/6.
//  Copyright © 2018年 Jinlong He. All rights reserved.
//

#ifndef Alias_hpp
#define Alias_hpp

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

using namespace std;
namespace nuxvm {
    class Var;
    class Value;
    class Atomic;
    class Conjunction;
    class Condition;
    class Transition;
    class NuXmv;

    typedef vector<Value*> Values;
    typedef vector<Var*> Vars;
    typedef vector<Atomic*> Atomics;
    typedef vector<Conjunction*> DNF;
    typedef vector<Transition*> Transitions;
    typedef vector<Transition*> Transitions;
    typedef vector<Condition*> Conditions;
    typedef size_t ID;
    
}
#endif /* Alias_hpp */

