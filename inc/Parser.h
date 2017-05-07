//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:25:27+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-07T18:20:32+02:00
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

#include <Automaton.h>

class Parser : public Automaton {
public:
	class bad_rule : public std::runtime_error {
	public:
		bad_rule(const char* what_arg);
		virtual ~bad_rule();
	};

	std::vector<std::string> symbols = {
		// "*",
		// "-",
		// " ",
		// "|",
		// "=",
		// ";",
		// "."

		":=",
		" ",
		";",
		"|"
	};


	Parser(void);
	Parser(std::string grammar_file);
	virtual ~Parser();

	void load(std::string rule);
};
