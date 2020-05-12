#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "ICommand.h"

class Validator
{
public:
	static bool validateCommand(ICommand* cmd, std::string input);
};
#endif // !VALIDATOR_H

