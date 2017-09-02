#include "Script.h"

Script::Script() {
    m_name = "DefaultScriptName";
    m_lastTimeTriggered = 0;
    m_autoTrigger = false;
    m_enabledTrigger = true;
}

Script::~Script() {

}

bool Script::hasTrigger(const std::string & trigger) const {
    for(std::string s : m_events)
        if(s.find(trigger) != s.npos)
            return true;
    return false;
}

bool Script::isEnabled() const {
    return m_enabledTrigger;
}
