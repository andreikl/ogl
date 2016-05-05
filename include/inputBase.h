class Application;

class InputBase {
public:
	InputBase();

	virtual void handle(const Application& app) = 0;
};
