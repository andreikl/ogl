#include "app.h"

class Tutorial1 : Application {
public:
    static Application* Create();

protected:
    virtual int draw();
};
