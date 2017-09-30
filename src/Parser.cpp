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

std::tuple<std::string, std::string, std::string> get_group(std::string s, char begin, char end ) {
	int i = s.find(begin);
	if (i != -1) {
		std::string A = s.substr(0, i + 1);
		std::string B = s.substr(i + 1, -1);

		int j = B.find(end);
		if (j != -1) {
			std::string C = B.substr(0, j);
			std::string D = B.substr(j, -1);

			return std::make_tuple(A, C, D);
		}
	}
	return s;
}

std::vector<std::string> tokenize(std::string s, std::string sep)
{
	std::vector<std::string> stack;

	int i = s.find(sep);
	// std::cout << s << " find " << sep << " : " << i << std::endl;

	if (i != -1) {
		std::vector<std::string> A = tokenize(s.substr(0, i), sep);
		std::copy(A.begin(), A.end(), std::back_inserter(stack));
		std::vector<std::string> B = tokenize(s.substr(i + sep.length(), -1), sep);
		std::copy(B.begin(), B.end(), std::back_inserter(stack));
	}
	else
		stack.push_back(s);

	// stack.push_back(s);
	stack.erase(std::remove_if(stack.begin(), stack.end(), [](std::string s){ return s == ""; }), stack.end());
	return stack;
}

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
	std::cout << std::endl;
	std::cout << Color::start(CYAN) << "Parser::load " << Color::end() << std::endl;
	std::cout << Color::start(MAGENTA) << rule << Color::end() << std::endl;

	rule = std::regex_replace(rule, std::regex("\\s*\\|\\s*"), "|");
	std::cout << rule << std::endl << std::endl;

	std::vector<std::string> tmp = tokenize(rule, ":=");
	Automaton *A = new Automaton(tmp[0]);
	State * current = new State(tmp[1]);
	A->states.push_back(current);
	A->start = A->states[0];

	std::vector<ACallable *> _ = A->states;
	A->states.clear();
	std::for_each(_.begin(), _.end(), [&](ACallable *a) {
		std::vector<std::string> tmp = tokenize(a->toString(), " ");
		ACallable * acc = NULL;
		std::for_each(tmp.begin(), tmp.end(), [&](std::string s){
			ACallable * a = new State(s);
			if (acc) {
				std::cout << acc->toString() << " ? " << a->toString() << std::endl;
				acc->truthy = a;
			}
			acc = a;
			A->states.push_back( a );
		});
	});
	A->start = A->states[0];

	// std::cout << "/ \\" << std::endl;
	// std::cout << A->toString() << std::endl;

	_ = A->states;
	A->states.clear();
	ACallable * acc = NULL;
	std::for_each(_.begin(), _.end(), [&](ACallable *a) {
		std::vector<std::string> tmp = tokenize(a->toString(), ";");
		std::for_each(tmp.begin(), tmp.end(), [&](std::string s){
			if (a->toString() != s) {
				ACallable * _a = new State(s);
				if (acc) {
					std::cout << acc->toString() << " ? " << _a->toString() << std::endl;
					acc->truthy = _a;
				}
				acc = _a;
				A->states.push_back( _a );
			}
			else {
				if (a->truthy && a->truthy->toString() == ";")
					a->truthy = NULL;
				A->states.push_back( a );
			}
		});
	});
	A->start = A->states[0];

	// std::cout << "/ \\" << std::endl;
	// std::cout << A->toString() << std::endl;

	_ = A->states;
	A->states.clear();
	acc = NULL;
	std::for_each(_.begin(), _.end(), [&](ACallable *a) {
		std::vector<std::string> tmp = tokenize(a->toString(), "|");
		std::for_each(tmp.begin(), tmp.end(), [&](std::string s){
			ACallable * _a = new State(s);
			if (a->toString() != s) {
				if (acc)
					acc->truthy = a->truthy;
				if (acc && acc->truthy != NULL)
					_a->truthy = acc->truthy;

				if (acc)
					acc->falsy = _a;

				acc = _a;
				A->states.push_back( _a );
			}
			else {
				delete _a;
				_a = NULL;
				A->states.push_back( a );
			}
			std::for_each(A->states.begin(), A->states.end(), [&](ACallable * tmp) {
				if (tmp->truthy == a && _a != NULL) {
					tmp->truthy = _a;
				}
			});
		});
		acc = NULL;
	});

	std::for_each(A->states.begin(), A->states.end(), [&](ACallable * tmp) {
		if (tmp->truthy == NULL) {
			// std::cout << tmp->toString() << std::endl;
			A->accept_states.push_back(tmp);
		}
	});

	A->start = A->states[0];

	std::for_each(A->states.begin(), A->states.end(), [&](ACallable * tmp) {
		tmp->setString(std::regex_replace(tmp->toString(), std::regex("\\\""), ""));
	});

	std::cout << std::endl;
	std::cout << A->toString() << std::endl;

	(*A)("1");
	(*A)("0");
	(*A)("01");
	(*A)("12");
	(*A)("14");
}

Parser::bad_rule::bad_rule(const char* what_arg) : std::runtime_error(what_arg) {}
Parser::bad_rule::~bad_rule() {}
