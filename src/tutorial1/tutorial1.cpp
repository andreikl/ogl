#include "tutorial1.h"

Application* Tutorial1::Create() {
    auto tutorial1 = new Tutorial1();
    tutorial1->initOpenGl();
    tutorial1->initApplication();
    return tutorial1;
}


int Tutorial1::draw() {
    return 0;
}
