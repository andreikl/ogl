class Application;

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
};
