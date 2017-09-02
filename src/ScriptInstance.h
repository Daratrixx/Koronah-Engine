/* 
 * File:   ScriptInstance.h
 * Author: ANTOINE
 *
 * Created on 17 décembre 2016, 22:34
 */

#ifndef SCRIPTINSTANCE_H
#define SCRIPTINSTANCE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef SCRIPT_H
#include "Script.h"
#endif

class ScriptInstance {
public:
    ScriptInstance(Script* script);
    ~ScriptInstance();
    
    void setArg(const UInt & argId, void* argValue);
    void* getArg(const UInt & argId);
    std::string getNextAction();
    void continueScript();
    bool canContinue() const;
    bool isDone() const;
    
    Script* m_script;
    UInt m_progression;
    float m_waitTime;
    // arg list
    std::map<UInt, void*> m_args;
};



#endif /* SCRIPTINSTANCE_H */

