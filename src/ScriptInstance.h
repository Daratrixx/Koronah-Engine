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
    
    void setArg(unsigned argId, void* argValue);
    void* getArg(unsigned argId);
    std::string getNextAction();
    void continueScript();
    bool canContinue();
    
    Script* m_script;
    unsigned int m_progression;
    float m_waitTime;
    bool m_done;
    // arg list
    std::map<unsigned, void*> m_args;
};



#endif /* SCRIPTINSTANCE_H */

