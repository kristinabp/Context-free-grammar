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

	void help();
	void open(std::string fileName);
	void close();
	void saveAs(std::string fileName);
	void exit();

	void list();
	void print(const std::string id);
	void save(const std::string id, const std::string fileName);
	void addRule(const std::string id, const std::string rule);
	void removeRule(const std::string id, int index);
	void unionn(const std::string& id1, const std::string& id2);

};
#endif // !GRAMMARSET_H

