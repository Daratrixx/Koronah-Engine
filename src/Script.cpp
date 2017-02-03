#include "Script.h"

Script::Script() {
    m_lastTimeTriggered = 0;
    m_autoTrigger = false;
    m_enabledTrigger = true;
}

Script::~Script() {

}

bool Script::hasTrigger(std::string trigger) {
    for(std::string s : m_events)
        if(s.find(trigger) != s.npos)
            return true;
    return false;
}

bool Script::isEnabled() {
    return m_enabledTrigger;
}
