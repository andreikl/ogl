// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "core.hpp"
#include "app.hpp"

#include "tutorial1.hpp"
#include "tutorial2.hpp"

int main(void) {
    //auto app = Tutorial1::Create();
    auto app = Tutorial2::Create();
    app->run();
    delete app;
}
