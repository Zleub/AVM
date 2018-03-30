//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:26:42+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-17T20:42:59+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <Color.h>
#include <Parser.h>

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
	else {
		for (auto x: m)
			std::cout << x << std::endl;
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
