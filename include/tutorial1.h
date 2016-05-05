#include "app.h"

class Tutorial1 : Application {
public:
    static Application* Create();

protected:
    virtual void draw();
    virtual void initWorld();
    virtual void dispose();
};
