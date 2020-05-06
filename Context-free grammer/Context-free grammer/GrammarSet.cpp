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

	std::string firstPart, secondPart;
	int i = 0;
	while (rule[i] != '-')
	{
		firstPart.push_back(rule[i]);
		i++;
	}
	i += 2;
	while (i < rule.size())
	{
		secondPart.push_back(rule[i]);
		i++;
	}

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
				if(grammarSet[i].)
				break;
			}
		}
	}
}

void GrammarSet::removeRule(std::string id, int index)
{
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id)
		{
			grammarSet[i]->removeRule(index-1);
			break;
		}
	}
	std::cout << "Incorrect Id\n";
}
