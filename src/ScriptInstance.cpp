#include "ScriptInstance.h"

ScriptInstance::ScriptInstance(Script* script) {
    m_script = script;
    m_progression = 0;
    m_waitTime = -1;
    m_done = false;
}

ScriptInstance::~ScriptInstance() {
    for (std::map<unsigned, void*>::iterator it = m_args.begin(); it != m_args.end(); ++it) {
        if (it->first > SCRIPT_ARG_FLOAT_TO_DELETE)
            delete (float*) it->second;
    }
    m_args.clear();
}

void ScriptInstance::setArg(unsigned argId, void* argValue) {
    m_args[argId] = argValue;
}

void* ScriptInstance::getArg(unsigned argId) {
    return m_args[argId];
}

std::string ScriptInstance::getNextAction() {
    return m_script->m_actions[m_progression];
}

void ScriptInstance::continueScript() {
    m_progression++;
}

bool ScriptInstance::canContinue() {
    return m_progression < m_script->m_actions.size() && m_waitTime <= 0;
}
