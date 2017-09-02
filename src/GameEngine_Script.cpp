#include "GameEngine.h"

void GameEngine::scriptMain() {
    std::queue<ScriptInstance*> scriptInstanceQueue;
    scriptInstanceQueue.swap(m_scriptInstanceQueue);
    while (!scriptInstanceQueue.empty()) {
        ScriptInstance* si = scriptInstanceQueue.front();
        si->m_waitTime -= m_tickDuration;
        runScript(si);
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
    //std::cout << "Script is running" << std::endl;
    while (si->canContinue()) {
        //std::cout << "Script continue" << std::endl;
        parseAction(si, si->getNextAction());
        si->continueScript();
    }
    if (!si->isDone()) {
        //std::cout << "Script paused(" << si->m_waitTime << ")" << std::endl;
        m_scriptInstanceQueue.push(si);
    } //else std::cout << "Script ended" << std::endl;
}

bool GameEngine::parseCondition(ScriptInstance *si, const std::string & condition) {
    return true;
}

void GameEngine::parseAction(ScriptInstance *si, std::string action) {
    //std::cout << "parse action: " << action << std::endl;
    if (scriptStartsWith(action, "script")) { // script action
       // std::cout << "script action" << std::endl;
        action = action.substr(std::strlen("script"));
        if (scriptStartsWith(action, "Wait")) {
            //std::cout << "Wait" << std::endl;
            std::vector<std::string> args = scriptArguments(action);
            float waitTime = scriptToFloat(si, args[0]);
            si->m_waitTime = waitTime;
        }
    } else if (scriptStartsWith(action, "unit")) { // unit action
        //std::cout << "unit action" << std::endl;
        action = action.substr(4);
        if (scriptStartsWith(action, "Create")) {
            //std::cout << "Create" << std::endl;
            std::vector<std::string> args = scriptArguments(action);
            Unit* unitType = scriptToUnit(si, args[0]);
            Player* owner = scriptToPlayer(si, args[1]);
            glm::vec2 position = scriptToPosition(si, args[2]);
            unitCreate(unitType, owner, position);
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
    unsigned textClosed = true;
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
                if (currentFunction[end] == ',' && parenthesisCount == 0 && textClosed)
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
        if (u != null) {
            std::cout << u->m_ownerId << std::endl;
            return u->m_ownerId;
        }
        std::cout << 0 << std::endl;
        return 0;
    }
    return 0;
}

glm::vec2 GameEngine::scriptToPosition(ScriptInstance* si, const std::string & script) {
    //std::cout << "scriptToPosition: " << script << std::endl;
    if (scriptStartsWith(script, "vec2")) {
        std::vector<std::string> args = scriptArguments(script);
        float x = scriptToFloat(si, args[0]), y = scriptToFloat(si, args[1]);
        std::cout << x << "," << y << std::endl;
        return glm::vec2(x, y);
    }
    if (scriptStartsWith(script, "unitPosition")) {
        std::vector<std::string> args = scriptArguments(script);
        Unit* u = scriptToUnit(si, args[0]);
        if (u != null) {
            float x = u->m_position.x, y = u->m_position.y;
            //std::cout << x << "," << y << std::endl;
            return glm::vec2(x, y);
        }
    }
    if (scriptStartsWith(script, "areaCenter")) {
        std::vector<std::string> args = scriptArguments(script);
        glm::vec4 a = scriptToArea(si, args[0]);
        float x = (a.x + a.z) / 2, y = (a.y + a.w) / 2;
        //std::cout << x << "," << y << std::endl;
        return glm::vec2(x, y);
    }
    if (scriptStartsWith(script, "playerStartPosition")) {
        std::vector<std::string> args = scriptArguments(script);
        Player* p = scriptToPlayer(si, args[0]);
        if (p != null) {
            float x = p->m_startingPosition.x, y = p->m_startingPosition.y;
            //std::cout << x << "," << y << std::endl;
            return glm::vec2(x, y);
        }
    }
    //std::cout << 0 << "," << 0 << std::endl;
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

int GameEngine::scriptToInt(ScriptInstance* si, const std::string & script) {
    //std::cout << "scriptToInt: " << script << std::endl;
    if (scriptStartsWith(script, "+(") || scriptStartsWith(script, "addition")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        //std::cout << a << "+" << b << "=" << a + b << std::endl;
        return (int) (a + b);
    }
    if (scriptStartsWith(script, "-(") || scriptStartsWith(script, "soustraction")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        //std::cout << a << "-" << b << "=" << a - b << std::endl;
        return (int) (a - b);
    }
    if (scriptStartsWith(script, "*(") || scriptStartsWith(script, "multiplication")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        //std::cout << a << "*" << b << "=" << a * b << std::endl;
        return (int) (a * b);
    }
    if (scriptStartsWith(script, "/(") || scriptStartsWith(script, "division")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        if (b == 0) { // avoid division by 0
            //std::cout << a << "/" << b << "=" << 0 << " !! DIV BY 0" << std::endl;
            return 0;
        }
        std::cout << a << "/" << b << "=" << a / b << ")" << std::endl;
        return (int) (a / b);
    }
    if (scriptStartsWith(script, "randomIntBetween")) {
        std::vector<std::string> args = scriptArguments(script);
        int a = scriptToInt(si, args[0]), b = scriptToInt(si, args[1]);
        int random = randomIntBetween(a, b);
        //std::cout << a << "," << b << "-> " << random << std::endl;
        return random;
    }
    if (scriptStartsWith(script, "unitOwnerId")) {
        std::vector<std::string> args = scriptArguments(script);
        Unit* u = scriptToUnit(si, args[0]);
        if (u != null) {
            //std::cout << u->m_ownerId << std::endl;
            return u->m_ownerId;
        }
        //std::cout << 0 << std::endl;
        return 0;
    }
    int r = toInt(script);
    //std::cout << r << std::endl;
    return r;
}

float GameEngine::scriptToFloat(ScriptInstance* si, const std::string & script) {
    //std::cout << "scriptToFloat: " << script << std::endl;
    if (scriptStartsWith(script, "+(") || scriptStartsWith(script, "addition")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        //std::cout << a << "+" << b << "=" << a + b << std::endl;
        return (a + b);
    }
    if (scriptStartsWith(script, "-(") || scriptStartsWith(script, "soustraction")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        //std::cout << a << "-" << b << "=" << a - b << std::endl;
        return (a - b);
    }
    if (scriptStartsWith(script, "*(") || scriptStartsWith(script, "multiplication")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        //std::cout << a << "*" << b << "=" << a * b << std::endl;
        return (a * b);
    }
    if (scriptStartsWith(script, "/(") || scriptStartsWith(script, "division")) {
        std::vector<std::string> args = scriptArguments(script);
        float a = scriptToFloat(si, args[0]), b = scriptToFloat(si, args[1]);
        if (b == 0) { // avoid division by 0
            //std::cout << a << "/" << b << "=" << 0 << " !! DIV BY 0" << std::endl;
            return 0;
        }
        //std::cout << a << "/" << b << "=" << a / b << std::endl;
        return (a / b);
    }
    if (scriptStartsWith(script, "randomFloatBetween")) {
        std::vector<std::string> args = scriptArguments(script);
        int a = scriptToInt(si, args[0]), b = scriptToInt(si, args[1]);
        float random = randomFloatBetween(a, b);
        //std::cout << a << "," << b << "-> " << random << std::endl;
        return random;
    }
    if (scriptStartsWith(script, "randomFloat")) {
        float random = randomFloat();
        //std::cout << "-> " << random << std::endl;
        return random;
    }
    if (scriptStartsWith(script, "unitOwnerId")) {
        std::vector<std::string> args = scriptArguments(script);
        Unit* u = scriptToUnit(si, args[0]);
        if (u != null) {
            //std::cout << u->m_ownerId << std::endl;
            return u->m_ownerId;
        }
        //std::cout << 0 << std::endl;
        return 0;
    }
    float r = toFloat(script);
    //std::cout << r << std::endl;
    return r;
}

std::string GameEngine::scriptToString(ScriptInstance* si, const std::string & script) {
    return script;
}
