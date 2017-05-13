//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:25:27+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-08T18:51:02+02:00
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

	struct loading_assoc {
		std::string symbol;
		void (*f)(Automaton **, std::deque<std::string> *);
	};

	// std::vector<loading_assoc> symbols = {
	// 	{ ":=", [](Automaton **A, std::deque<std::string> * v) {
	// 		std::string tmp = (*v)[0];
	// 		(*v).pop_front();
	//
	// 		*A = new Automaton(tmp);
	// 		std::cout << Color::start(RED) << (*A)->toString() << Color::end() << std::endl;
	// 	} },
	// 	{ " ", [](Automaton **A, std::deque<std::string> * v) {
	// 		std::deque<std::string> *tmp = new std::deque<std::string>();
	// 		std::for_each(v->begin(), v->end(), [&](std::string s){
	// 			if (static_cast<int>(s.find_first_of(";|")) == -1) {
	// 				(*A)->states.push_back( new State(s) );
	// 				std::cout << Color::start(BLUE) << s << Color::end() << std::endl;
	// 			}
	// 			else
	// 				(*tmp).push_back(s);
	//
	// 		});
	// 		*v = *tmp;
	// 	} },
	// 	{ ";", [](Automaton **A, std::deque<std::string> * v) {
	// 		std::deque<std::string> *tmp = new std::deque<std::string>();
	// 		std::for_each(v->begin(), v->end(), [&](std::string s){
	// 			if (static_cast<int>(s.find_first_of("|")) == -1) {
	// 				(*A)->states.push_back( new State(s) );
	// 				std::cout << Color::start(MAGENTA) << s << Color::end() << std::endl;
	// 			}
	// 			else
	// 				(*tmp).push_back(s);
	//
	// 		});
	// 		*v = *tmp;
	// 	} },
	// 	{ "|", [](Automaton **A, std::deque<std::string> * v) {
	// 		std::for_each(v->begin(), v->end(), [&](std::string s){
	// 			(*A)->states.push_back( new State(s) );
	// 			std::cout << Color::start(YELLOW) << s << Color::end() << std::endl;
	// 		});
	// 	} }
	// };


	Parser(void);
	Parser(std::string grammar_file);
	virtual ~Parser();

	void load(std::string rule);
private:
};
