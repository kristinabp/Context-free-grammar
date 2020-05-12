#include "AddRuleCommand.h"



AddRuleCommand::AddRuleCommand(GrammarSet& receiver):receiver(receiver)
{
}

void AddRuleCommand::execute()
{
	receiver.addRule(parameters[1], parameters[2]);
}

void AddRuleCommand::unexecute()
{
}

std::string AddRuleCommand::toString()
{
	return "addrule";
}
