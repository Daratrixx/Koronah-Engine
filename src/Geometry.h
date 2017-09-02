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

glm::vec3 getForwardVector(const glm::vec3 & angle);
glm::vec3 getBackVector(const glm::vec3 & angle);
glm::vec3 getRightVector(const glm::vec3 & angle);
glm::vec3 getLeftVector(const glm::vec3 & angle);
glm::vec3 getUpVector(const glm::vec3 & angle);
glm::vec3 getDownVector(const glm::vec3 & angle);
bool isPointInRectangle(const glm::vec2 & point, const glm::vec2 & center, const glm::vec2 & size);
bool isPointInCircle(const glm::vec2 & point, const glm::vec2 & center, const float & radius);

// http://jeux.developpez.com/tutoriels/theorie-des-collisions/formes-complexes/
bool isPointInPolygon(const glm::vec2 tab[], const UShort & nbp, const glm::vec2 & P);


glm::vec2 positionAlongLine(const glm::vec2 & origin, const glm::vec2 & destination, const float & distance);

#endif	/* GEOMETRY_H */

