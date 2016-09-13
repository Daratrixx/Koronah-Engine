/* 
 * File:   Time.h
 * Author: ANTOINE
 *
 * Created on 17 juin 2016, 23:46
 */
#pragma once

#ifndef TIME_H
#define	TIME_H

#ifndef TYPES_H
#include "Types.h"
#endif


class TimeEngine {
public:
    TimeEngine();
    float getDeltaTime();
    float getCurrentTime();
    float getCurrentTick();
    void updateTime();
    void waitSeconds(float seconds);
    int getFPS();
    
private:
    float CURRENT_TIME;
    float DELTA_TIME;
    float UPDATE_CUMULATOR;
    int UPDATE_COUNT;
    int LAST_UPDATE_COUNT;
    int FPS_APPROX;
};

#endif	/* TIME_H */

