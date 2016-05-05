#include "tutorial1.h"

int main(void) {
    auto app = Tutorial1::Create();
    app->run();
    delete app;
}
