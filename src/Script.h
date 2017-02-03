/* 
 * File:   Script.h
 * Author: ANTOINE
 *
 * Created on 17 décembre 2016, 22:37
 */

#ifndef SCRIPT_H
#define SCRIPT_H

#ifndef TYPES_H
#include "Types.h"
#endif

class Script {
public:
    Script();
    ~Script();

    bool hasTrigger(std::string trigger);
    bool isEnabled();

    float m_lastTimeTriggered;
    bool m_autoTrigger;
    bool m_enabledTrigger;
    std::vector<std::string> m_events;
    std::vector<std::string> m_conditions;
    std::vector<std::string> m_actions;
};

#endif /* SCRIPT_H */

