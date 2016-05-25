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
#include "tutorial3.hpp"

int main(void) {
    //auto app = Tutorial1::Create();
    //auto app = Tutorial2::Create();
    auto app = Tutorial3::Create();
    app->run();
    delete app;
}
