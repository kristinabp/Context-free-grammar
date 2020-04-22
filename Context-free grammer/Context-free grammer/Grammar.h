#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Rule.h"
#include <iostream>
#include <vector>
#include <string>


class Grammar
{
private: 
	std::vector<Rule*> rules;
	std::string id;

	void copy(const Grammar& other);

public:
	Grammar();
	Grammar(const std::vector<Rule*> rules, const std::string id);
	Grammar(const Grammar& other);
	~Grammar();

	Grammar& operator=(const Grammar& other);

	Grammar& addRule(Rule* rule);
	void removeRule(int n);

	void print()const;

};
#endif // !GRAMMER_H

