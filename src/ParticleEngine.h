/* 
 * File:   ParticleEngine.h
 * Author: ANTOINE
 *
 * Created on 6 juillet 2016, 23:19
 */

#ifndef PARTICLEENGINE_H
#define	PARTICLEENGINE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef PARTICLE_H
#include "Particle.h"
#endif

#ifndef PARTICLEMODIFIER_H
#include "ParticleModifier.h"
#endif

#ifndef MODEL_H
#include "Model.h"
#endif

#ifndef SORTEDKEYFRAME_HPP
#include "SortedKeyChain.hpp"
#endif

#ifndef GRAPHICENGINE_H
#include "GraphicEngine.h"
#endif

#ifndef GEOMETRY_H
#include "Geometry.h"
#endif


class ParticleEngine {
public:
    ParticleEngine();
    ~ParticleEngine();
    void mainFunction(float time); // function to call
    void clean();
    void update(float time); // transform all particles
    void sort();
    void generate(); // create the arrays
    void render();
    void createParticle(glm::vec3 position); // before mainFunction in a tick
private:
    int m_particleCount;
    std::vector<Particle*> m_particles;
    std::vector<ParticleModifier*> m_modifiers;
    SortedKeyChain* m_paticleToRender;
    glm::vec3* m_position;
    float* m_opacity;
    float* m_size;
    int* m_texture;
};

#endif	/* PARTICLEENGINE_H */

