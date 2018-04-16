#include <Automaton.h>

Automaton::Automaton(std::string cmp) : cmp(cmp) {};
Automaton::~Automaton() {};

std::string Automaton::toString(void) {
	return toString(0);
}

std::string Automaton::toString(int indent) {
	std::stringstream ss;

	ss << cmp << std::endl <<
	std::string(indent * 2, ' ') << "| truthy -> " << (truthy ? truthy->toString(indent + 1) : "null") << std::endl <<
	std::string(indent * 2, ' ') << "| falsy -> " << (falsy ? falsy->toString(indent + 1) : "null") ;

	return ss.str();
}

int Automaton::operator()(std::string s) {
	int b = !s.compare(0, cmp.length(), cmp);

	// std::cout << s << " -- " << cmp << " : " << (b ? "true" : "false") << std::endl;

	if (b && truthy) {
		b &= (*truthy)(s.substr(cmp.length()));
	}
	else if (!b && falsy) {
		b |= (*falsy)(s);
	}
	else
		b &= (s.length() == 0 || s.substr(cmp.length()).length() == 0);

	return b;
}
