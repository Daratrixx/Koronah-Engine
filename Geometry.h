/* 
 * File:   Geometry.h
 * Author: ANTOINE
 *
 * Created on 4 juillet 2016, 20:32
 */

#ifndef GEOMETRY_H
#define	GEOMETRY_H

#ifndef TYPES_H
#include "Types.h"
#endif

glm::vec3 getForwardVector(glm::vec3 angle);
glm::vec3 getBackVector(glm::vec3 angle);
glm::vec3 getRightVector(glm::vec3 angle);
glm::vec3 getLeftVector(glm::vec3 angle);
glm::vec3 getUpVector(glm::vec3 angle);
glm::vec3 getDownVector(glm::vec3 angle);
bool isPointInRectangle(glm::vec2 point, glm::vec2 center, glm::vec2 size);
bool isPointInCircle(glm::vec2 point, glm::vec2 center, float radius);

// http://jeux.developpez.com/tutoriels/theorie-des-collisions/formes-complexes/
bool isPointInPolygon(glm::vec2 tab[], unsigned int nbp, glm::vec2 P);


glm::vec2 positionAlongLine(glm::vec2 origin, glm::vec2 destination, float distance);

#endif	/* GEOMETRY_H */

