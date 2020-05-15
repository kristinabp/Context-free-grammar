#include "CloseCommand.h"

void CloseCommand::execute()
{
	receiver.close();
}

void CloseCommand::unexecute()
{
}

std::string CloseCommand::toString()
{
	return "close";
}

CloseCommand::CloseCommand(GrammarSet & receiver):receiver(receiver)
{
}
