#include "Grammar.h"

int Grammar::counter = 0;

bool Grammar::checkTerminal (const char& ch) const
{
	if (ch >= 'a' && ch <= 'z')
	{
		return true;
	}
	else if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Grammar::checkTerminalSet(const char& ch) const
{
	for (size_t i = 0; i < terminals.size(); i++)
	{
		if (ch == terminals[i])
		{
			return true;
		}
	}
	return false;
}

bool Grammar::checkVariablesSet(const char& ch) const
{
	for (size_t i = 0; i < variables.size(); i++)
	{
		if (ch == variables[i][0])
		{
			return true;
		}
	}
	return false;
}

bool Grammar::checkUpper(const char& ch) const
{
	return ch >= 'A' && ch <= 'Z';
}

bool Grammar::checkVariable(const std::string& ch) const
{
	return ch[0]>='A' && ch[0]<='Z';
}

void Grammar::copy(const Grammar & other)
{
	this->rules = other.rules;
	this->id = other.id;
	this->variables = other.variables;
	this->terminals = other.terminals;
	this->startVariable = other.startVariable;
}

void Grammar::createId()
{
	std::string i = std::to_string(counter) + '-' + startVariable;
	this->id = i;
}

Grammar::Grammar() : rules(std::vector<Rule*>()), id("X-X"), variables(std::vector<std::string>()), terminals(std::vector<char>()),
					startVariable()
{
	this->counter++;
}

Grammar::Grammar(const std::vector<Rule*>& rules, const std::vector<std::string> variables, const std::vector<char> terminals, const char startVariable)
{
	for (size_t i = 0; i < variables.size(); i++)
	{
		if (checkVariable(variables[i]))
		{
			this->variables.push_back(variables[i]);
		}
		else
		{
			std::cout << "Incorrect variables set.\n";
			assert(false);
		}
	}

	for (size_t i = 0; i < terminals.size(); i++)
	{
		if (checkTerminal(terminals[i]))
		{
			this->terminals.push_back(terminals[i]);
		}
		else
		{
			std::cout << "Incorrect terminals set.\n";
			assert(false);
		}
	}

	bool flag = false;
	if (checkUpper(startVariable))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (variables[i][0] == startVariable)
			{
				this->startVariable = startVariable;
				flag = true;
			}
		}

		if (!flag)
		{
			std::cout << "Incorrect starting variable.Does not exist in variable set.\n";
			assert(false);
		}
	}
	else if (startVariable == '$')
	{
		this->startVariable = startVariable;
		flag = true;
	}
	else
	{
		std::cout << "Incorrect starting variable.\n";
		assert(false);
	}

	for (size_t i = 0; i < rules.size(); i++)
	{
		addRule(rules[i]); //validate the rules
	}

	this->counter++;
	createId();
}

Grammar::Grammar(const Grammar & other)
{
	copy(other);
}

Grammar::~Grammar()
{
}

Grammar & Grammar::operator=(const Grammar & other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}

std::string Grammar::getId() const
{
	return this->id;
}

std::vector<std::string> Grammar::getVariables() const
{
	return this->variables;
}

std::vector<char> Grammar::getTerminals() const
{
	return this->terminals;
}

std::vector<Rule*> Grammar::getRules() const
{
	return this->rules;
}

char Grammar::getStartVariable() const
{
	return this->startVariable;
}

void Grammar::setStartingVariable(const char & var)
{
	this->startVariable = var;
}

void Grammar::addNewVariable(const std::string & var)
{
	if (!checkVariablesSet(var[0]))
	{
		this->variables.push_back(var);
	}
}

Grammar * Grammar::clone() const
{
	return new Grammar(*this);
}

void Grammar::addRule(const Rule * r)
{
	bool variableCheck = true;
	if (checkVariable(r->getVariable()))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (r->getVariable() == variables[i])
			{
				variableCheck = true;
				break;
			}
			else
			{
				variableCheck = false;
			}
		}
	}
	else if (r->getVariable() == "$")
	{
		variableCheck = true;
	}
	else
	{
		std::cout << "Incorrect variable.\n";
		assert(false);
	}

	bool productionCheck = true;
	if (r->getProduction().size() != 0) // checks if there is any productions
	{
		for (size_t i = 0; i < r->getProduction().size(); i++)
		{
			if (r->getProduction()[i].size() != 0) // checks if there is an empty production
			{
				for (size_t j = 0; j < r->getProduction()[i].size(); j++)//checks if the production is valid
				{
					if (checkTerminalSet(r->getProduction()[i][j])) // if the current char is terminal
					{
						continue;
					}
					else if (checkUpper(r->getProduction()[i][j]))//if the current char is an upper letter
					{
						for (size_t k = 0; k < variables.size(); k++) // if it is check if the letter is in the set of variables
						{
							if (r->getProduction()[i][j] == variables[k][0])
							{
								productionCheck = true;
								break;
							}
							else
							{
								productionCheck = false; //if it is not we make this flag false
							}
						}

						if (!productionCheck) 
						{
							break;
						}
					}
					else if (r->getProduction()[i][j] == '$') // this symbol cames from the iter function
					{
						continue;
					}
					else
					{
						std::cout << "Incorrect productions.\n";
						assert(false);
					}
				}
			}
			else
			{
				std::cout << "Empty production.\n";
				assert(false);
			}
		}
	}
	else
	{
		std::cout << "Empty productions.\n";
		assert(false);
	}

	if (variableCheck && productionCheck)
	{
		this->rules.push_back(r->clone());
	}
	else
	{
		assert(false);
	}
}

void Grammar::removeRule(int index)
{
	if (index<=rules.size())
	{
		for (size_t i = 0; i < rules.size(); i++)
		{
			if (index-1 == i)
			{
				rules.erase(rules.begin() + i);
				std::cout << "Rule removed.\n";
				break;
			}
		}
	}
	else
	{
		std::cout << "Incorrect index.\n";
	}
}

void Grammar::save(std::ostream & os)
{
	for (size_t i = 0; i < variables.size()-1; i++)
	{
		os << variables[i] << " ";
	}
	os << variables[variables.size() - 1];
	os << '\n';
	for (size_t i = 0; i < terminals.size()-1; i++)
	{
		os << terminals[i] << " ";
	}
	os << terminals[terminals.size() - 1 ];
	os << '\n';
	os << startVariable;
	os << '\n';
	os << rules.size();
	os << '\n';
	for (size_t i = 0; i < rules.size(); i++)
	{
		rules[i]->print(os);
		os << '\n';
	}
}

void Grammar::chomsky() const
{
	bool chomskyCheck = true;
	for (size_t i = 0; i < rules.size(); i++)
	{
		if (rules[i]->getProduction().size() < 2) // check if we have more than one production A->BC|a
		{
			if (rules[i]->getProduction()[0].size() == 1 && checkTerminal(rules[i]->getProduction()[0][0]))
			{ //check if the production length is 1 and if it is it should be a terminal A->a
				chomskyCheck = true;
			}
			else if (rules[i]->getProduction()[0].size() == 2 && 
			(checkUpper(rules[i]->getProduction()[0][0]) && rules[i]->getProduction()[0][0] != startVariable) && 
			(checkUpper(rules[i]->getProduction()[0][1]) && rules[i]->getProduction()[0][1] != startVariable))
			{//check if the production length is 2 and if it is it should be two upper cases(here we don't check if they are
			// from the set of variables because we validate the rules when we add them and here we know that they are valid)
			// and also this upper cases should be different from the start variable
				chomskyCheck = true;
			}
			else
			{
				chomskyCheck = false;
				break;
			}
		}
		else
		{
			chomskyCheck = false;
			break;
		}

	}

	if (chomskyCheck)
	{
		std::cout << "The grammar is in normal Chomsky form.\n";
	}
	else
	{
		std::cout << "The grammar is not in normal Chomsky form.\n";
	}
}

void Grammar::iter()
{
	addNewVariable("$");
	char oldStartVariable = getStartVariable();
	setStartingVariable('$');
	addRule(new Rule("$", { "$" + oldStartVariable }));
}

void Grammar::print() const
{
	if (variables.size() > 1)
	{
		for (size_t i = 0; i < variables.size() - 1; i++)
		{
			std::cout << variables[i] << ", ";
		}
	}
	std::cout << variables[variables.size()-1] << "\t";
	if (terminals.size() > 1)
	{
		for (size_t i = 0; i < terminals.size() - 1; i++)
		{
			std::cout << terminals[i] << ", ";
		}
	}
	if (!terminals.size() == 0)
	{
		std::cout << terminals[terminals.size() - 1];
	}
	std::cout << "\t "<<startVariable << "\n";
	for (size_t i = 0; i < rules.size(); i++)
	{
		std::cout << i + 1 << ".";
		rules[i]->print(std::cout);
		std::cout << "\n";
	}
}
