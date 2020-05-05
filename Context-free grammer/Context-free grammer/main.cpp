#include "GrammarSet.h"

int main()
{
	Rule r1('S', { "ab", "K" });
	Rule r2('K', { "kk", "K"});
	std::vector<Rule*> r;
	r.push_back(new Rule(r1));
	Grammar g(r, { "S","K" }, {'a', 'k', 'b'}, 'S');
	g.addRule(&r1);
	g.print();
	GrammarSet s;
	s.addGrammar(&g);
	s.save("1-K-1","grammar.txt");
	return system("pause");
}  