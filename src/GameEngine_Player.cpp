
#include "GameEngine.h"

void GameEngine::initPlayers() {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        if (m_players[i] != null)
            delete m_players[i];
        m_players[i] = new Player();
        m_players[i]->m_playerId = PLAYER_1 + i;
        switch (m_players[i]->m_playerId) {
            case PLAYER_1:
                m_players[i]->m_teamColor = TEAM_COLOR_1;
                break;
            case PLAYER_2:
                m_players[i]->m_teamColor = TEAM_COLOR_2;
                break;
            case PLAYER_3:
                m_players[i]->m_teamColor = TEAM_COLOR_3;
                break;
            case PLAYER_4:
                m_players[i]->m_teamColor = TEAM_COLOR_4;
                break;
            case PLAYER_5:
                m_players[i]->m_teamColor = TEAM_COLOR_5;
                break;
            case PLAYER_6:
                m_players[i]->m_teamColor = TEAM_COLOR_6;
                break;
            case PLAYER_7:
                m_players[i]->m_teamColor = TEAM_COLOR_7;
                break;
            case PLAYER_8:
                m_players[i]->m_teamColor = TEAM_COLOR_8;
                break;
        }
        for(unsigned int j = 0; j < PLAYER_COUNT; j++) {
            m_playerRelation[i][j] = PLAYER_RELATION_ENEMY;
        }
    }
}

bool GameEngine::playerIsAlly(Player* p1, Player* p2) {
    return (m_playerRelation[p1->m_playerId][p1->m_playerId] & PLAYER_RELATION_ALLY) == PLAYER_RELATION_ALLY;
}

void GameEngine::playerSetAlly(Player* p1, Player* p2) {
    m_playerRelation[p1->m_playerId][p1->m_playerId] |= PLAYER_RELATION_ALLY;
}

bool GameEngine::playerIsEnemy(Player* p1, Player* p2) {
    return (m_playerRelation[p1->m_playerId][p1->m_playerId] & PLAYER_RELATION_ALLY) == 0;
}

void GameEngine::playerSetEnemy(Player* p1, Player* p2) {
    m_playerRelation[p1->m_playerId][p1->m_playerId] &= ~PLAYER_RELATION_ALLY;
}
