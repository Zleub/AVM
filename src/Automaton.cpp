#include <Automaton.h>

Automaton::Automaton(std::string cmp) : cmp(cmp) {};
Automaton::~Automaton() {};

std::string Automaton::toString() {
	return cmp;
}

int Automaton::operator()(std::string s) {
	return !s.compare(0, cmp.length(), cmp);
}
