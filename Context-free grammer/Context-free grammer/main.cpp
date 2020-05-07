#include "GrammarSet.h"

int main()
{
	Rule r('A', { "aa" });
	Rule r1('B', { "b" });
	Grammar g({}, { 'A', 'B'}, {}, 'A');
	g.addRule(&r);
	g.addRule(&r1);
	GrammarSet gs({&g});
	gs.addRule("1-A", "A->a|b");
	gs.print("1-A");
	gs.removeRule("1-A", 4);
	gs.help();
	return system("pause");
}  