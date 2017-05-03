//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:25:27+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-03T20:38:42+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

class Parser {
public:
	class bad_rule : public std::runtime_error {
	public:
		bad_rule(const char* what_arg);
		virtual ~bad_rule();
	};

	Parser();
	Parser(std::string grammar_file);
	virtual ~Parser();

	void load(std::string rule);
	void process(std::string line);
	std::string toString(void);

private:
	class Rule {
	public:
		Rule(std::string name, std::string regex);
		virtual ~Rule();

		std::string name;
		std::string sregex;
		std::regex regex;
	};

	std::regex parse_rule = std::regex("([A-Z]+)\\s*:=\\s*(.+)");
	std::vector<Rule *> rules;
	std::string acc;

	void _load(std::string rule);
	void _expand(void);
};
