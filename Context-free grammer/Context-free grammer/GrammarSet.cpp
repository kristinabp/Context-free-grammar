#include "GrammarSet.h"

GrammarSet::GrammarSet(): grammarSet(std::vector<Grammar*>())
{
}

GrammarSet::GrammarSet(std::vector<Grammar*> grammars)
{
	this->grammarSet = grammars;
}

void GrammarSet::addGrammar(const Grammar * grammar)
{
	this->grammarSet.push_back(grammar->clone());
}

void GrammarSet::help()
{
	std::cout << "> help\n";
	std::cout << "------ The following commands are supported : -------------------------------------------------\n";
	std::cout << "|open <file>				opens <file>\n";
	std::cout << "|close					closes currently opened file\n";
	std::cout << "|save <id> <fileName>			saves a grammar in a file\n";
	std::cout << "|saveas <file>				saves the currently open file in <file>\n";
	std::cout << "|help					prints this information\n";
	std::cout << "|exit					exists the program\n";
	std::cout << "|addgrammar <grammarName>		adds new grammar\n";
	std::cout << "|list 					lists all grammar ids\n";
	std::cout << "|print <id>				prints a grammar\n";
	std::cout << "|addRule <id> <rule> 			adds a new rule\n";
	std::cout << "|removeRule <id> <n> 			removes a rule with a number\n";
	std::cout << "-----------------------------------------------------------------------------------------------\n";
}

void GrammarSet::exit()
{
	std::cout << "> exit\n";
	std::cout << "Exiting the program...\n";
}

void GrammarSet::list()
{
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		std::cout << grammarSet[i]->getId();
	}
}

void GrammarSet::print(std::string id)
{
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (id == grammarSet[i]->getId())
		{
			grammarSet[i]->print();
		}
	}
}

void GrammarSet::save(std::string id, std::string fileName)
{
	std::ofstream myfile;
	myfile.open(fileName);
	if (myfile.good())
	{
		for (size_t i = 0; i < grammarSet.size(); i++)
		{
			if (grammarSet[i]->getId() == id)
			{
				grammarSet[i]->save(myfile);
				myfile.close();
				std::cout << "Successfully saved as " << fileName << "\n";
				return;
			}
			else
			{
				std::cout << "Grammar with this id does not exist.\n";
			}
		}
		myfile.close();
		std::cout << "Could not saved as " << fileName << "\n";
		
	}
	else
	{
		std::cout << "Couldn't open " << fileName << "\n";
	}
}

void GrammarSet::addRule(const std::string id, const std::string rule)
{
	if (rule == "")
	{
		std::cout << "Incorrect input.\n";
	}

	if (!rule.find("->"))
	{
		std::cout << "Incorrect input.\n";
	}

	std::string firstPart, curr;
	std::vector<std::string> secondPart;
	int i = 0;
	while (rule[i] != '-')
	{
		firstPart.push_back(rule[i]);
		i++;
	}
	i += 2;
	while (i < rule.size())
	{
		while (rule[i] != '|' && i < rule.size())
		{
			curr.push_back(rule[i]);
			i++;
		}
		secondPart.push_back(curr);
		curr = "";
		i++;
	}

	bool findGrammar = true;
	if (firstPart.size() >= 2)
	{
		std::cout << "Incorrect input.\n";
	}
	else
	{
		for (size_t i = 0; i < grammarSet.size(); i++)
		{
			if (grammarSet[i]->getId() == id)
			{
				findGrammar = true;
				grammarSet[i]->addRule(new Rule(firstPart[0],secondPart));
				break;
			}
			else
			{
				findGrammar = false;
			}
		}
		if (findGrammar)
		{
			std::cout << "Sucessfully added rule " << firstPart << " -> ";
			for (size_t i = 0; i < secondPart.size(); i++)
			{
				std::cout << secondPart[i] << " | ";
			}
			std::cout << std:: endl;
		}
		else
		{
			std::cout << "Couldn't find grammar with this id.\n";
		}
	}
}

void GrammarSet::removeRule(std::string id, int index)
{
	bool flag = true;
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id)
		{
			grammarSet[i]->removeRule(index);
			flag = true;
			break;
		}
		else
		{
			flag = false;
		}
	}
	if (!flag)
	{
		std::cout << "Incorrect Id.\n";
	}
}

void GrammarSet::unionn(const std::string & id1, const std::string & id2)
{
	if (id1 == id2)
	{
		std::cout << "Try to union the same grammars grammar.\n";
		assert(false);
	}

	//first step: arrange it so the two grammars have no variables(non-terminals) in common

	
	Grammar* newGrammar=nullptr;
	Grammar* firstGrammar = nullptr;
	Grammar* secondGrammar=nullptr;
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id1)
		{
			firstGrammar = grammarSet[i];
			break;
		}
	}

	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id2)
		{
			secondGrammar = grammarSet[i];
			break;
		}
	}
	std::vector<std::string> firstVar;
	for (size_t i = 0; i < firstGrammar->getVariables().size(); i++)
	{
		firstVar.push_back(firstGrammar->getVariables()[i]);
	}
	
	for (size_t i = 0; i < secondGrammar->getVariables().size(); i++)
	{
		if (std::find(firstVar.begin(), firstVar.end(), secondGrammar->getVariables()[i]) != firstVar.end())
		{
			newGrammar->addNewVariable(secondGrammar->getVariables()[i] + "2");
		}
		else
		{
			newGrammar->addNewVariable(secondGrammar->getVariables()[i]);
		}
	}

	newGrammar->print();
}
