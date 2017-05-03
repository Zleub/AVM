//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:26:42+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-03T20:39:57+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <Color.h>
#include <Parser.h>

Parser::Parser() {}
Parser::Parser(std::string grammar_file) {
	std::string line;
	std::ifstream f(grammar_file);

	if (f.is_open()) {
		while (!f.eof()) {
			getline(f, line);
			try {
				load(line);
			} catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
		f.close();
		if ( 0 != f.eof() ) {
			std::cout << Color::start(GREEN) << "Grammar loaded" << Color::end() << std::endl;
		}
	}
	else {
		std::cout << Color::start(RED) << "Grammar error" << Color::end() << std::endl;
	}
}
Parser::~Parser() {}

void Parser::load(std::string rule) {
	std::smatch sm;
	std::regex_match(rule, sm, parse_rule);
	if (sm.size() != 3) {
		if (rule == "") {
			if (acc != "")
				_load(acc);
			acc = "";
			return ;
		}

		(acc == "") ? acc = rule : acc += " " + rule;
		return ;
	}
	_load(rule);
}

void Parser::_load(std::string rule) {
	std::smatch sm;

	std::regex_match(rule, sm, parse_rule);
	if (sm.size() != 3)
		throw bad_rule(("Not a valid rule: " + Color::start(RED) + rule + Color::end()).c_str());

	std::cout << Color::start(GREEN) << "New rule: " << Color::end() << rule << std::endl;
	rules.push_back( new Rule(sm[1], sm[2]) );
}

void Parser::process(std::string line) {
	std::cout << Color::start(CYAN) << "~ line: " << Color::end() << line << std::endl;

	std::for_each(rules.begin(), rules.end(), [line](Rule * r) {
		std::smatch sm;
		std::cout << r->sregex << std::endl;
		std::cout << std::regex_match(line, sm, r->regex) << std::endl;
	});
}

std::string Parser::toString(void) {
	std::stringstream s;

	std::for_each( rules.begin(), rules.end(), [&s](Rule *r){
		s << r->name << ": " << r->sregex << std::endl;
	});

	return s.str();
}

Parser::bad_rule::bad_rule(const char* what_arg) : std::runtime_error(what_arg) {}
Parser::bad_rule::~bad_rule() {}

Parser::Rule::Rule(std::string name, std::string regex) : name(name) {
	std::smatch sm;

	std::cout << Color::start(BLUE) << regex << Color::end() << std::endl;

	this->sregex = regex ;

	regex = std::regex_replace(regex, std::regex("\\.\\."), "-");
	regex = std::regex_replace(regex, std::regex("\\."), "\\.");
	regex = std::regex_replace(regex, std::regex("\\("), "\\(");
	regex = std::regex_replace(regex, std::regex("\\)"), "\\)");
	regex = std::regex_replace(regex, std::regex("\\s+\\|\\s+"), "|");

	this->regex = std::regex(regex);
}
Parser::Rule::~Rule() {}
