#include <Color.h>
#include <Automaton.h>

Parser::Parser(void) {
	std::string line;

	while (getline(std::cin, line)) {
		load(line);
	}
}
Parser::Parser(std::string grammar_file) {
	std::ifstream f(grammar_file);
	std::string line;

	if (!f.is_open()) {
		getline(std::cin, line);
		load(line);
	}
}
Parser::~Parser() {}

void Parser::load(std::string rule) {
	std::cout << "Parser: " << rule << std::endl;

	std::smatch m;
	std::regex e ("(\\w+)\\s+:=\\s+(.+)");

	std::regex_search(rule, m, e);

	if (m.empty())
		std::cout << "No match" << std::endl;
	else if (m.size() == '3') {
		std::string name = m[1];
		std::string expr = m[2];

		automatonMap.insert( std::pair<std::string, std::vector<Automaton*>>(name, new std::vector<Automaton *>()) );
	}

}

int Parser::operator()(std::string) {
	std::cout << "Parser::operator()" << std::endl;
	return 0;
}

std::string Parser::toString() {
	return "Parser::toString";
}

Parser::bad_rule::bad_rule(const char* what_arg) : std::runtime_error(what_arg) {}
Parser::bad_rule::~bad_rule() {}
