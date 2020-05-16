#include "Invoker.h"

Invoker::Invoker() : receiver(new GrammarSet())
{
	commands.push_back(new OpenCommand(*receiver));
	commands.push_back(new HelpCommand(*receiver));
	commands.push_back(new ExitCommand(*receiver));
	commands.push_back(new ListCommand(*receiver));
	commands.push_back(new PrintCommand(*receiver));
	commands.push_back(new SaveCommand(*receiver));
	commands.push_back(new RemoveRuleCommand(*receiver));
	commands.push_back(new AddRuleCommand(*receiver));
	commands.push_back(new SaveAsCommand(*receiver));
	commands.push_back(new CloseCommand(*receiver));
	commands.push_back(new ChomskyCommand(*receiver));
}

Invoker::Invoker(ICommand * command) : receiver(new GrammarSet())
{
	commands.push_back(command);
}

Invoker::~Invoker()
{
}

void Invoker::executeCommand(std::string input)
{

	for (ICommand* cmd : commands)
	{
		if (Validator::validateCommand(cmd, input))
		{
			cmd->addParameters(input);
			cmd->execute();
			return;
		}
	}

	std::cout << "Use command name.\n";
}