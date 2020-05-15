#include "GrammarSet.h"
#include "Invoker.h"

int main()
{
	std::cout;
	Invoker remote;
	std::string input;
	while (true)
	{
		getline(std::cin, input);
		remote.executeCommand(input);
	}

	return system("pause");
}  