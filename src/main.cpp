#include <Automata.h>

class Sandbox : public Automata::Application {
public:
	Sandbox()
	{
	}
	~Sandbox() {}
};

int main()
{
	Automata::Application* app = new Sandbox();
	app->Run();
	app->ShutDown();

	delete app;
}