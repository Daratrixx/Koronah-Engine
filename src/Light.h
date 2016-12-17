/* 
 * File:   Light.h
 * Author: ANTOINE
 *
 * Created on 16 juillet 2016, 19:32
 */

#ifndef LIGHT_H
#define	LIGHT_H

#ifndef TYPES_H
#include "Types.h"
#endif

class Light {
public:
    Light();
    ~Light();
    void setData(float* dataOrigin);
    glm::vec3 getPosition() const;
    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);
    glm::vec3 getColor() const;
    void setColor(float r, float g, float b);
    void setColor(glm::vec3 color);
    float getEnergy() const;
    void setEnergy(float energy);
    void UpdateColor();
private:
    float* m_data;
    glm::vec3 m_color;
    float m_energy;
};

#endif	/* LIGHT_H */

