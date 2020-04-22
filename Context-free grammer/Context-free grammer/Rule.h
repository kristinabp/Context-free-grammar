#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <string>

class Rule
{
private:
	char variable;
	std::string terminals;

	void copy(const Rule& other);

public:
	Rule();
	Rule(const char variable, const std::string terminals);
	Rule(const Rule& other);
	~Rule();

	Rule* clone() const;

	char getVariable()const;
	std::string getTerminals()const;


	Rule& operator=(const Rule& other);

	void print()const;
};
#endif // !RULE_H

