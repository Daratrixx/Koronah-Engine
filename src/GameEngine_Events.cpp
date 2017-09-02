#include "GameEngine.h"

void GameEngine::unitEntersGame(Unit* unit) {
    //std::cout << "unitEntersGame" << std::endl;
    for (std::vector<Script*>::iterator it = m_scriptList.begin(); it != m_scriptList.end(); it++) {
        Script* s = *it;
        if (s->isEnabled() && s->hasTrigger("unitEntersGame")) {
            ScriptInstance* si = new ScriptInstance(s);
            si->setArg(SCRIPT_ARG_TRIGGERING_UNIT, unit);
            if (checkConditions(si))
                runScript(si);
        }
    }
}

void GameEngine::unitDealsDamage(Unit* damaging, Unit* damaged, const float & damage) {
    //std::cout << "unitDealsDamage" << std::endl;
    for (std::vector<Script*>::iterator it = m_scriptList.begin(); it != m_scriptList.end(); it++) {
        Script* s = *it;
        if (s->isEnabled() && s->hasTrigger("unitDealsDamage")) {
            ScriptInstance* si = new ScriptInstance(s);
            si->setArg(SCRIPT_ARG_TRIGGERING_UNIT, damaging);
            si->setArg(SCRIPT_ARG_DAMAGED_UNIT, damaged);
            si->setArg(SCRIPT_ARG_DAMAGING_UNIT, damaging);
            si->setArg(SCRIPT_ARG_DAMAGES_AMOUNT, new float(damage));
            if (checkConditions(si))
                runScript(si);
        }
    }
}

void GameEngine::unitTakesDamage(Unit* damaged, Unit* damaging, const float & damage) {
    //std::cout << "unitTakesDamage" << std::endl;
    for (std::vector<Script*>::iterator it = m_scriptList.begin(); it != m_scriptList.end(); it++) {
        Script* s = *it;
        if (s->isEnabled() && s->hasTrigger("unitTakesDamage")) {
            ScriptInstance* si = new ScriptInstance(s);
            si->setArg(SCRIPT_ARG_TRIGGERING_UNIT, damaged);
            si->setArg(SCRIPT_ARG_DAMAGED_UNIT, damaged);
            si->setArg(SCRIPT_ARG_DAMAGING_UNIT, damaging);
            si->setArg(SCRIPT_ARG_DAMAGES_AMOUNT, new float(damage));
            if (checkConditions(si))
                runScript(si);
        }
    }
}

void GameEngine::unitKills(Unit* killer, Unit* dead) {
    //std::cout << "unitKills" << std::endl;
    for (std::vector<Script*>::iterator it = m_scriptList.begin(); it != m_scriptList.end(); it++) {
        Script* s = *it;
        if (s->isEnabled() && s->hasTrigger("unitKills")) {
            ScriptInstance* si = new ScriptInstance(s);
            si->setArg(SCRIPT_ARG_TRIGGERING_UNIT, killer);
            si->setArg(SCRIPT_ARG_KILLING_UNIT, killer);
            si->setArg(SCRIPT_ARG_DYING_UNIT, dead);
            if (checkConditions(si))
                runScript(si);
        }
    }
}

void GameEngine::unitDies(Unit* dead, Unit* killer) {
    //std::cout << "unitDies" << std::endl;
    for (std::vector<Script*>::iterator it = m_scriptList.begin(); it != m_scriptList.end(); it++) {
        Script* s = *it;
        if (s->isEnabled() && s->hasTrigger("unitDies")) {
            ScriptInstance* si = new ScriptInstance(s);
            si->setArg(SCRIPT_ARG_TRIGGERING_UNIT, dead);
            si->setArg(SCRIPT_ARG_KILLING_UNIT, killer);
            si->setArg(SCRIPT_ARG_DYING_UNIT, dead);
            if (checkConditions(si))
                runScript(si);
        }
    }
}

void GameEngine::unitEntersArea(Unit* unit, glm::vec4 area) {
    //std::cout << "unitEntersArea" << std::endl;
    for (std::vector<Script*>::iterator it = m_scriptList.begin(); it != m_scriptList.end(); it++) {
        Script* s = *it;
        if (s->isEnabled() && s->hasTrigger("unitEntersArea")) {
            ScriptInstance* si = new ScriptInstance(s);
            si->setArg(SCRIPT_ARG_TRIGGERING_UNIT, unit);
            si->setArg(SCRIPT_ARG_ENTERING_UNIT, unit);
            si->setArg(SCRIPT_ARG_TRIGGERING_AREA, new glm::vec4(area));
            si->setArg(SCRIPT_ARG_ENTERED_AREA, new glm::vec4(area));
            if (checkConditions(si))
                runScript(si);
        }
    }
}

void GameEngine::unitLeavesArea(Unit* unit, glm::vec4 area) {
    //std::cout << "unitLeavesArea" << std::endl;
    for (std::vector<Script*>::iterator it = m_scriptList.begin(); it != m_scriptList.end(); it++) {
        Script* s = *it;
        if (s->isEnabled() && s->hasTrigger("unitLeavesArea")) {
            ScriptInstance* si = new ScriptInstance(s);
            si->setArg(SCRIPT_ARG_TRIGGERING_UNIT, unit);
            si->setArg(SCRIPT_ARG_LEAVING_UNIT, unit);
            si->setArg(SCRIPT_ARG_TRIGGERING_AREA, new glm::vec4(area));
            si->setArg(SCRIPT_ARG_LEAVED_AREA, new glm::vec4(area));
            if (checkConditions(si))
                runScript(si);
        }
    }
}
