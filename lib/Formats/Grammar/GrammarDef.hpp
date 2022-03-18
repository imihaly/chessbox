//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#undef STATE
#undef SWITCH
#undef PASS
#undef FAIL


#define STATE(stateName, onEnter)\
case stateName:\
    onEnter;

#define SWITCH(condition, nextState, onSwitch) \
    if(condition(c)) {\
        onSwitch;\
        state = nextState;\
        return true;\
    }\

#define PASS(nextState, onSwitch)\
onSwitch;\
    state = nextState;\
    continue;

#define FAIL(x)\
    return false;
