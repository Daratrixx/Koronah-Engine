/* 
 * File:   ParticleModifier.h
 * Author: ANTOINE
 *
 * Created on 3 août 2016, 14:31
 */

#ifndef PARTICLEMODIFIER_H
#define	PARTICLEMODIFIER_H


#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

typedef struct {
    glm::vec3 position;
    glm::vec3 direction;
    float powerReduction;
    float radius;
} ParticleModifier;

#endif	/* PARTICLEMODIFIER_H */

