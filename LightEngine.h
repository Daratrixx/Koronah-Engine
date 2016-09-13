/* 
 * File:   LightEngine.h
 * Author: ANTOINE
 *
 * Created on 16 juillet 2016, 19:47
 */

#ifndef LIGHTENGINE_H
#define	LIGHTENGINE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef LIGHT_H
#include "Light.h"
#endif

class LightEngine {
public:
    LightEngine();
    ~LightEngine();
    Light* getLight(unsigned int index);
    float* getLightData() const;
private:
    float* m_lightData;
    Light** m_lightArray;
};

#endif	/* LIGHTENGINE_H */

