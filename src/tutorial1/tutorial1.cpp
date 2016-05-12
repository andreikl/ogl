// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "particle.h"
#include "inputOrbit.h"

#include "tutorial1.h"

ParticleBase* particle;

Application* Tutorial1::Create() {
    auto tutorial1 = new Tutorial1();
    tutorial1->init();
    return tutorial1;
}

void Tutorial1::initWorld() {
    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    particle = ParticleSphere::Create();
}

void Tutorial1::draw() {
    particle->draw(*this);
}

void Tutorial1::dispose() {
    Application::dispose();

    delete particle;
    delete input;
}
