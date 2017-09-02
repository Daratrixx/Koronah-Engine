/* 
 * File:   Player.h
 * Author: ANTOINE
 *
 * Created on 24 septembre 2016, 15:19
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "Types.h"

typedef struct {
    std::string m_name;
    UShort m_playerId;
    glm::vec3 m_teamColor;
    glm::vec2 m_startingPosition;
    UShort m_race;
    
    UInt m_energy;
    UInt m_materials;
    
    UInt m_unitLimit;
    UInt m_unitCount;
} Player;

#endif	/* PLAYER_H */

