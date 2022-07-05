#include <Automata.h>
int main()
{
	Automata::Core.Init();
	Automata::Core.Run();
	Automata::Core.ShutDown();

	return 0;
}