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
#include "tutorial4.hpp"

/*int main(void) {
    //auto app = Tutorial1::Create();
    //auto app = Tutorial2::Create();
    //auto app = Tutorial3::Create();
    auto app = Tutorial4::Create();
    app->run();
    delete app;
}*/

#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);

    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}