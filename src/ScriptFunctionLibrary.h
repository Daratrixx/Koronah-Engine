
#ifndef SCRIPTFUNCTIONLIBRARY_H
#define SCRIPTFUNCTIONLIBRARY_H

#include "Types.h"
#include "ScriptNode.h"

////////////////////////////////////////////////////////
//
// How that works
//
// - First parameter is game engine (to access data)
// - All other parameters are values to be computed by the function
//
////////////////////////////////////////////////////////

ScriptValue function(ScriptNode** parameter) {
    ScriptValue out;
    //GameEngine* game = (GameEngine*)parameter[0]->getValue().value;
    return out;
}

#endif /* SCRIPTFUNCTIONLIBRARY_H */
