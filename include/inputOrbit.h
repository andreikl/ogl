#include "inputBase.h"

class InputOrbit: InputBase {
// construcots and destructors
public:
	InputOrbit(Application & app);
	~InputOrbit();

	static InputBase* create(Application & app, double radius);

// functions that are overrided
public:
	virtual void init();
	virtual void handle();

// functionality
private:
	void update();

private:
	// config
	double minRadius = 01.0;
	double maxRadius = 10.0;
	// rotation radius
	double radius;
	// scale factor and rotate angles
	double sf = 1.0;
	double rx = 0.0;
	double ry = 0.0;
	// mouse coordinates
	double mx;
	double my;
};
