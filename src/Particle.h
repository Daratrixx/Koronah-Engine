/* 
 * File:   Particle.h
 * Author: ANTOINE
 *
 * Created on 6 juillet 2016, 23:24
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

typedef struct {
    float remainingDuration;
    glm::vec3 position;
    glm::vec3 angle;
    UShort textureIndex;
} Particle;

#endif	/* PARTICLE_H */

