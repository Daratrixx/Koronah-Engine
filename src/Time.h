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
    float getDeltaTime() const;
    float getCurrentTime() const;
    float getCurrentTick() const;
    void updateTime();
    void waitSeconds(float seconds) const;
    UShort getFPS() const;
    
private:
    float CURRENT_TIME;
    float DELTA_TIME;
    float UPDATE_CUMULATOR;
    UShort UPDATE_COUNT;
    UShort LAST_UPDATE_COUNT;
    UShort FPS_APPROX;
};

#endif	/* TIME_H */

