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
    void setPosition(const float & x, const float & y, const float & z);
    void setPosition(const glm::vec3 & position);
    glm::vec3 getColor() const;
    void setColor(const float & r, const float & g, const float & b);
    void setColor(const glm::vec3 & color);
    float getEnergy() const;
    void setEnergy(const float & energy);
    void UpdateColor();
private:
    float* m_data;
    glm::vec3 m_color;
    float m_energy;
};

#endif	/* LIGHT_H */

