// stl
#include <iostream>
#include <math.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "config.h"
#include "app.h"
#include "inputOrbit.h"

InputOrbit* that = nullptr;

InputOrbit::InputOrbit(Application & app): InputBase(app) {
}

InputOrbit::~InputOrbit() {
	that = nullptr;
}

InputBase* InputOrbit::create(Application& app, double radius) {
	if (that) {
		throw "instance of InputBase is already created!";
	}
	that = new InputOrbit(app);
	that->radius = radius;

	that->init();
	that->update();
	return that;
}

void InputOrbit::init() {
	glfwSetMouseButtonCallback(this->app.getWindow(), [] (GLFWwindow* window, int button, int action, int mods) -> void {
		//std::cout << button << " " << action << " " << mods << std::endl;
	});

	glfwSetScrollCallback(this->app.getWindow(), [] (auto window, auto xoffset, auto yoffset) {
		if (yoffset > 0) {
			that->sf += 0.1;
			that->update();
		} else if (yoffset < 0) {
			that->sf -= 0.1;
			that->update();
		}
		//std::cout << "scale: " << that->sf << std::endl;
	});

}

void InputOrbit::handle() {
	auto posx = 0.0;
	auto posy = 0.0;
	glfwGetCursorPos(this->app.getWindow(), &posx, &posy);

	if (GLFW_PRESS == glfwGetMouseButton(app.getWindow(), GLFW_MOUSE_BUTTON_LEFT)) {
		// calculates deltas
		auto deltax = this->mx - posx;
		auto deltay = this->my - posy;
		// calculates rotate factor
		auto rfx = deltax / this->app.getWidth();
		auto rfy = deltay / this->app.getHeight();
		// calculates angle
		auto ax = 2 * PI * rfx;
		auto ay = 2 * PI * rfy;
		// updates angle
		this->rx += ax;
		this->ry -= ay;

		//std::cout << "handle: anglex: " << ax << ", " << rx << ", angley: " << ay << ", " << ry << std::endl;

		this->update();
	} else if (GLFW_PRESS == glfwGetMouseButton(app.getWindow(), GLFW_MOUSE_BUTTON_RIGHT)) {
	}
	this->mx = posx;
	this->my = posy;

}

void InputOrbit::update() {
	double r = this->radius * this->sf;
	if (r < this->minRadius) {
		this->sf = this->minRadius / this->radius;
		r = this->minRadius;
	} else if (r > this->maxRadius) {
		this->sf = this->maxRadius / this->radius;
		r = this->maxRadius;
	}
	auto x = r * sin(this->rx) * cos(this->ry);
	auto y = r * sin(this->ry);
	auto z = r * cos(this->rx) * cos(this->ry);
	std::cout << "update: x: " << x << ", y: " << y << ", z: " << z << std::endl;
	if (this->ry < PI / 2 && this->ry > -PI / 2) {
		app.setView(glm::lookAt(
			glm::vec3(x, y, z), // Camera position in World Space
			glm::vec3(0, 0, 0), // looks position
			glm::vec3(0, 1, 0) // Head vector
		));  
	} else {
		app.setView(glm::lookAt(
			glm::vec3(x, y, z), // Camera position in World Space
			glm::vec3(0, 0, 0), // looks position
			glm::vec3(0, -1, 0) // Head vector
		));
	}
}
