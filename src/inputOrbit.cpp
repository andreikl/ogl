// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "app.h"
#include "inputOrbit.h"

void InputOrbit::handle(const Application & app) {
	if (GLFW_PRESS == glfwGetMouseButton(app.getWindow(), GLFW_MOUSE_BUTTON_LEFT)) {
	}
}
