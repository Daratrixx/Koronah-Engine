/* 
 * File:   Player.h
 * Author: ANTOINE
 *
 * Created on 24 septembre 2016, 15:19
 */

#ifndef PLAYER_H
#define	PLAYER_H

class Player {
public:
    
private:
    std::string m_name;
    unsigned int m_playerID;
    unsigned int m_color;
    unsigned int m_race;
    
    unsigned int m_energy;
    unsigned int m_materials;
    
    unsigned int m_unitLimit;
    unsigned int m_unitCount;
};

#endif	/* PLAYER_H */

