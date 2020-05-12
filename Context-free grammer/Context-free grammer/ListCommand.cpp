#include "ListCommand.h"



ListCommand::ListCommand(GrammarSet& receiver):receiver(receiver)
{
}

void ListCommand::execute()
{
	receiver.list();
}

void ListCommand::unexecute()
{
}

std::string ListCommand::toString()
{
	return "list";
}
