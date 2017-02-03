#include "GameEngine.h"

void GameEngine::scriptMain() {
    std::queue<ScriptInstance*> scriptInstanceQueue;
    scriptInstanceQueue.swap(m_scriptInstanceQueue);
    while (!scriptInstanceQueue.empty()) {
        runScript(scriptInstanceQueue.front());
        scriptInstanceQueue.pop();
    }
}

bool GameEngine::checkConditions(ScriptInstance *si) {
    for (std::string s : si->m_script->m_conditions)
        if (!parseCondition(si, s))
            return false;
    return true;
}

void GameEngine::runScript(ScriptInstance *si) {
    std::cout << "Script is running" << std::endl;
    while (si->canContinue()) {
        parseAction(si, si->getNextAction());
        si->continueScript();
    }
    if (!si->m_done)
        m_scriptInstanceQueue.push(si);
}

bool GameEngine::parseCondition(ScriptInstance *si, const std::string & condition) {
    return true;
}

void GameEngine::parseAction(ScriptInstance *si, std::string action) {
    std::cout << "parse action: " << action << std::endl;
    if (action.substr(0, 4) == "unit") { // unit action
        std::cout << "unit action" << std::endl;
        action = action.substr(4);
        if (action.substr(0, 6) == "Create") {
            std::cout << "Create" << std::endl;
            std::vector<std::string> args = scriptArguments(action);
            Unit* unitType = scriptToUnit(si, args[0]);
            unsigned ownerId = scriptToPlayerId(si, args[1]);
            glm::vec2 position = scriptToPosition(si, args[2]);
            unitCreate(unitType, ownerId, position);
        }
    }
}

std::vector<std::string> GameEngine::scriptArguments(const std::string & function) {
    std::string currentFunction = function;
    std::vector<std::string> output;
    while (currentFunction[currentFunction.length() - 1] != ')') // remove after last parenthesis
        currentFunction = currentFunction.substr(0, currentFunction.length() - 1);
    if (currentFunction[currentFunction.length() - 1] == ')') // remove last parenthesis
        currentFunction = currentFunction.substr(0, currentFunction.length() - 1);
    while (currentFunction[0] != '(') // remove before first parenthesis
        currentFunction = currentFunction.substr(1);
    if (currentFunction[0] == '(') // remove first parenthesis
        currentFunction = currentFunction.substr(1);
    while (currentFunction[0] == ' ') // first spaces
        currentFunction = currentFunction.substr(1);
    while (currentFunction[currentFunction.length() - 1] == ' ') // last spaces
        currentFunction = currentFunction.substr(0, currentFunction.length() - 1);
    unsigned start = 0;
    unsigned end = 0;
    unsigned parenthesisCount = 0;
    unsigned textClosed = false;
    while (end < currentFunction.length()) {
        while (end < currentFunction.length()) {
            if (currentFunction[end] == ' ') {
                end++;
                continue;
            } else {
                if (currentFunction[end] == '(' && textClosed)
                    parenthesisCount++;
                if (currentFunction[end] == ')' && textClosed)
                    parenthesisCount--;
                if (currentFunction[end] == '"')
                    textClosed = !textClosed;
                if (currentFunction[end] == ',' && parenthesisCount == 0)
                    break;
                end++;
            }
        }
        std::string arg = currentFunction.substr(start, end - start);
        while (arg[0] == ' ') // first spaces
            arg = arg.substr(1);
        while (arg[arg.length() - 1] == ' ') // last spaces
            arg = arg.substr(0, arg.length() - 1);
        output.push_back(arg);
        end++;
        start = end;
        end++;
    }
    return output;
}

bool GameEngine::scriptStartsWith(const std::string & script, const std::string & start) {
    return script.substr(0, start.length()) == start;
}

Unit* GameEngine::scriptToUnit(ScriptInstance* si, const std::string & script) {
    if (script == "TRIGGERING_UNIT")
        return (Unit*) si->getArg(SCRIPT_ARG_TRIGGERING_UNIT);
    if (script == "KILLING_UNIT")
        return (Unit*) si->getArg(SCRIPT_ARG_KILLING_UNIT);
    if (script == "DYING_UNIT")
        return (Unit*) si->getArg(SCRIPT_ARG_DYING_UNIT);
    return null;
}

Player* GameEngine::scriptToPlayer(ScriptInstance* si, const std::string & script) {
    if (scriptStartsWith(script, "unitOwner")) {
        std::vector<std::string> args = scriptArguments(script);
        Unit* u = scriptToUnit(si, args[0]);
        if (u != null)
            return m_players[u->m_ownerId];
    }
    if (scriptStartsWith(script, "playerId")) {
        std::vector<std::string> args = scriptArguments(script);
        unsigned id = scriptToPlayerId(si, args[0]);
        return m_players[id];
    }
    return m_players[0];
}

unsigned GameEngine::scriptToPlayerId(ScriptInstance* si, const std::string & script) {
    if (scriptStartsWith(script, "unitOwnerId")) {
        std::vector<std::string> args = scriptArguments(script);
        Unit* u = scriptToUnit(si, args[0]);
        if (u != null)
            return u->m_ownerId;
    }
    return 0;
}

glm::vec2 GameEngine::scriptToPosition(ScriptInstance* si, const std::string & script) {
    if (scriptStartsWith(script, "unitPosition")) {
        std::vector<std::string> args = scriptArguments(script);
        Unit* u = scriptToUnit(si, args[0]);
        if (u != null)
            return glm::vec2(u->m_position);
    }
    if (scriptStartsWith(script, "areaCenter")) {
        std::vector<std::string> args = scriptArguments(script);
        glm::vec4 a = scriptToArea(si, args[0]);
        return glm::vec2((a.x + a.z) / 2, (a.y + a.w) / 2);
    }
    if (scriptStartsWith(script, "playerStartPosition")) {
        std::vector<std::string> args = scriptArguments(script);
        Player* p = scriptToPlayer(si, args[0]);
        if (p != null)
            return p->m_startingPosition;
    }
    return glm::vec2(0, 0);
}

glm::vec4 GameEngine::scriptToArea(ScriptInstance* si, const std::string & script) {
    if (script == "TRIGGERING_AREA")
        return glm::vec4(*((glm::vec4*)si->getArg(SCRIPT_ARG_TRIGGERING_AREA)));
    if (script == "ENTERED_AREA")
        return glm::vec4(*((glm::vec4*)si->getArg(SCRIPT_ARG_ENTERED_AREA)));
    if (script == "LEAVED_AREA")
        return glm::vec4(*((glm::vec4*)si->getArg(SCRIPT_ARG_LEAVED_AREA)));
    return glm::vec4(0, 0, 0, 0);
}
