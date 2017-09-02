#include "ScriptInstance.h"

ScriptInstance::ScriptInstance(Script* script) {
    m_script = script;
    m_progression = 0;
    m_waitTime = -1;
}

ScriptInstance::~ScriptInstance() {
    for (std::map<UInt, void*>::iterator it = m_args.begin(); it != m_args.end(); ++it) {
        if (it->first > SCRIPT_ARG_FLOAT_TO_DELETE)
            delete (float*) it->second;
    }
    m_args.clear();
}

void ScriptInstance::setArg(const UInt & argId, void* argValue) {
    m_args[argId] = argValue;
}

void* ScriptInstance::getArg(const UInt & argId) {
    return m_args[argId];
}

std::string ScriptInstance::getNextAction() {
    return m_script->m_actions[m_progression];
}

void ScriptInstance::continueScript() {
    m_progression++;
}

bool ScriptInstance::canContinue() const {
    return !isDone() && m_waitTime <= 0;
}

bool ScriptInstance::isDone() const {
    return m_progression == m_script->m_actions.size();
}
