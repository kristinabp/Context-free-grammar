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
