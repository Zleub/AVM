//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:25:27+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-05T18:28:32+02:00
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

	Parser(void);
	Parser(std::string grammar_file);
	virtual ~Parser();

	void load(std::string rule);
	void process(std::string line);
	std::string toString(void);

private:
	enum Quantifiers {
		NONE,
		ZERO_OR_ONE,  // ?
		ZERO_OR_MORE, // *
		ONE_OR_MORE,  // +
	};

	class Rule {
	public:
		Rule(std::string name, std::string regex, Quantifiers q = NONE);
		virtual ~Rule();

		std::string name;
		std::string text;
		std::string expansion;

		Quantifiers quantifier;
	};

	int anonyme_count;

	std::regex parse_rule = std::regex("([A-z]+)\\s*:=\\s*(.+)");
	std::vector<Rule *> rules;
	std::string acc;

	std::vector< std::tuple<char,char> > groups = {
		{ '[', ']' },
		{ '\'', '\'' }
	};

	std::vector< char > separators = {
		'|'
	};

	void _load(std::string rule);
	void _expand_group(void);
	void _expand_separator(void);
	Rule * _match_group(Rule * r, char begin, char end);
	Rule * _match_separator(Rule * r, char separator);
};
