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
        
#endif	/* GEOMETRY_H */

