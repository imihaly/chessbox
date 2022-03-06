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
    stateName,

#define SWITCH(condition, nextState, onSwitch) // NOP

#define PASS(nextState, onSwitch) // NOP

#define FAIL(x) // NOP
