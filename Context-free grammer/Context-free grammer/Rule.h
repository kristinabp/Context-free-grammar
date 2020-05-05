#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <string>
#include <vector>

class Rule
{
private:
	char variable;
	std::vector<std::string> terminals;

	void copy(const Rule& other);

public:
	Rule();
	Rule(const char variable, const std::vector<std::string> terminals);
	Rule(const Rule& other);
	~Rule();

	char getVariable()const;
	std::vector<std::string> getTerminals()const;

	Rule* clone() const;

	Rule& operator=(const Rule& other);

	void print(std::ostream& os)const;
};
#endif // !RULE_H

