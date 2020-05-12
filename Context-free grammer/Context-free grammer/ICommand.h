#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include <vector>

class ICommand
{
protected:
	std::vector< std::string> parameters;

public:
	virtual void execute() = 0;
	virtual void unexecute() = 0;

	void addParameters(std::string input);

	virtual std::string toString() = 0;
};
#endif // !ICOMMAND_H

