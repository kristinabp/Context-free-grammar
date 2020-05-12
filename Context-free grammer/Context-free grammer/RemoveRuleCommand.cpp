#include "RemoveRuleCommand.h"



RemoveRuleCommand::RemoveRuleCommand(GrammarSet& receiver):receiver(receiver)
{
}

void RemoveRuleCommand::execute()
{
	receiver.removeRule(parameters[1], stoi(parameters[2]));
}

void RemoveRuleCommand::unexecute()
{
}

std::string RemoveRuleCommand::toString()
{
	return "removerule";
}
