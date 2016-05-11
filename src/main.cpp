// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tutorial1.h"

int main(void) {
    auto app = Tutorial1::Create();
    app->run();
    delete app;
}
