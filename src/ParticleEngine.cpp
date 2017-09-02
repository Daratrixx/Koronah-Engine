
#include "ParticleEngine.h"

ParticleEngine::ParticleEngine() {
    m_paticleToRender = new SortedKeyChain();
    m_position = null;
    m_texture = null;
    m_particleCount = 0;
    ParticleModifier* pm = new ParticleModifier();
    pm->position = glm::vec3(0, 0, 0);
    pm->direction = glm::vec3(3, 15, 3);
    pm->radius = 5;
    m_modifiers.push_back(pm);
}

ParticleEngine::~ParticleEngine() {
    clean();
    delete m_paticleToRender;
    while (!m_particles.empty()) {
        delete m_particles[m_particles.size() - 1];
        m_particles.pop_back();
    }
    while (!m_modifiers.empty()) {
        delete m_modifiers[m_modifiers.size() - 1];
        m_modifiers.pop_back();
    }
}

void ParticleEngine::mainFunction(float time) {
    clean();
    update(time);
    sort();
    generate();
    render();
}

void ParticleEngine::clean() {
    delete m_position;
    delete m_texture;
    delete m_opacity;
    delete m_size;
    m_position = null;
    m_texture = null;
    m_opacity = null;
    m_size = null;
    m_paticleToRender->clear();
}

void ParticleEngine::update(float time) {
    std::vector<Particle*> toRemove;
    float gravityFactor = -9.8f * time;
    for (std::vector<Particle*>::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
        Particle* p = (Particle*) (*it);
        p->remainingDuration -= time;
        if (p->remainingDuration < 0)
            toRemove.push_back(p);
        else {
            for (std::vector<ParticleModifier*>::iterator it2 = m_modifiers.begin(); it2 != m_modifiers.end(); ++it2) {
                ParticleModifier* pm = (ParticleModifier*) (*it2);
                //float distance;
                //distance = glm::length(pm->position - p->position);
                //if (distance < pm->radius)
                    p->angle += pm->direction * time;
            }
            p->angle += glm::vec3(0, gravityFactor, 0);
            p->position = p->position + (glm::normalize(p->angle) * time * 2.5f);
        }
    }
    for (std::vector<Particle*>::iterator it = toRemove.begin(); it != toRemove.end(); ++it) {
        Particle* p = (Particle*) (*it);
        m_particles.erase(std::find(m_particles.begin(), m_particles.end(), p));
        delete p;
        m_particleCount--;
    }
}

void ParticleEngine::sort() {
    for (std::vector<Particle*>::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
        //Particle* p = (Particle*) (*it);
        //m_paticleToRender->add(m_graphicEngine->getCameraDistance(p->position), (void*) p);
    }
}

void ParticleEngine::generate() {
    m_position = new glm::vec3[m_particleCount];
    m_opacity = new float[m_particleCount];
    m_size = new float[m_particleCount];
    //m_texture = new int[m_particleCount];
    UInt i = 0;
    KeyLink* current = m_paticleToRender->first;
    while (current != null) {
        Particle* p = (Particle*) (current->value);
        *(m_position + i) = p->position;
        *(m_opacity + i) = 0.1f + p->remainingDuration / 5.f;
        *(m_size + i) = 0.1f + glm::clamp(10.f / p->remainingDuration, 0.5f, 1.5f);
        //*(m_texture + i) = p->textureIndex;
        current = current->next;
        i++;
    }
}

void ParticleEngine::render() {
    //m_graphicEngine->renderParticle(m_position, m_opacity, m_size, m_particleCount);
}

void ParticleEngine::createParticle(glm::vec3 position) {
    if (m_particleCount == PARTICLE_MAX_COUNT) {
        delete m_particles[0];
        m_particles.erase(m_particles.begin());
    } else m_particleCount++;
    Particle* p = new Particle();
    p->position = position;
    float op = (float) ((rand() % 30));
    p->angle = getForwardVector(glm::vec3(op, rand() % 360, 0));
    p->remainingDuration = 2;
    m_particles.push_back(p);
}
