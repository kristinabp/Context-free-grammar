#ifndef GRAMMARSET_H
#define GRAMMARSET_H

#include "Grammar.h"
#include <fstream>
#include <iostream>

class GrammarSet
{
private:
	std::vector<Grammar*> grammarSet;

public:
	GrammarSet();
	GrammarSet(std::vector<Grammar*> grammars);

	void addGrammar(const Grammar* grammar);

	void list();
	void print(std::string id);
	void save(std::string id, std::string fileName);
	void addRule(std::string id, const Rule& rule);
	void removeRule(std::string id, const Rule& rule);

};
#endif // !GRAMMARSET_H

