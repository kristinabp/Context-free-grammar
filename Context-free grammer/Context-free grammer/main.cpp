#include "Grammar.h"

int main()
{
	Grammar g;
	g.addRule(new Rule('S', "ab")).addRule(new Rule('K', "k")).addRule(new Rule('A',"K"));
	g.removeRule(2);
	g.print();
	return system("pause");
}