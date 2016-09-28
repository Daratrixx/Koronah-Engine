/* 
 * File:   GameEnigine.h
 * Author: ANTOINE
 *
 * Created on 24 septembre 2016, 15:42
 */

#ifndef GAMEENIGINE_H
#define	GAMEENIGINE_H

class GameEngine {
public:


protected:
    Player* m_players[8];
    Unit* m_units[200 * 8];
    Unit* m_playerUnits[8][200];
    //Upgrade m_techTree[8];
    unsigned char** m_collisionMap;
    float m_gameTime;
    float m_dayTime;

    // Cell* m_cells;


};

#endif	/* GAMEENIGINE_H */

