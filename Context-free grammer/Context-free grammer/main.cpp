#include "Grammar.h"

int main()
{
	Rule r1('S', { "ab", "K" });
	Rule r2('K', { "kk", "K"});
	Grammar g({ &r1, &r2 }, "XXX", { 'S', 'K' }, { "kk","ab" }, 'S');
	//g.addRule(new Rule('S', { "ab", "K", "AK" })).addRule(new Rule('K', { "kk", "A" })).addRule(new Rule('A', { "a" }));
	g.print();
	
	return system("pause");
}