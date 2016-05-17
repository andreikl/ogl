// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "core.h"
#include "app.h"

#include "tutorial1.h"
#include "tutorial2.h"

int main(void) {
    //auto app = Tutorial1::Create();
    auto app = Tutorial2::Create();
    app->run();
    delete app;
}
