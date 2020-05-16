#ifndef INVOKER_H
#define INVOKER_H

#include "OpenCommand.h"
#include "HelpCommand.h"
#include "ICommand.h"
#include "ExitCommand.h"
#include "ListCommand.h"
#include "PrintCommand.h"
#include "SaveCommand.h"
#include "RemoveRuleCommand.h"
#include "AddRuleCommand.h"
#include "SaveAsCommand.h"
#include "CloseCommand.h"
#include "ChomskyCommand.h"
#include "Validator.h"

class Invoker
{
private:
	std::vector <ICommand *> commands;
	GrammarSet* receiver;

public:
	Invoker();
	Invoker(ICommand* command);
	~Invoker();

	void executeCommand(std::string input);
};
#endif // !INVOKER_H

