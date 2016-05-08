class Application;

enum Status: int {
	NONE = 0,
	ROTATE = 1,
	ZOOM = 2,
	TRANSLATE = 4
};

class InputBase {
// constructors and destructors
public:
	InputBase(Application & app);

// methods
public:
	virtual void init() = 0;
	virtual void handle() = 0;

// variables
protected:
	Application & app;
	int status = Status::NONE;
};
