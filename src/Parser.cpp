//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:26:42+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-07T18:55:41+02:00
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
	std::cout << rule << std::endl;

	std::vector<std::string> stack = { rule };
	std::for_each(symbols.begin(), symbols.end(), [&](std::string symbol) {
		std::vector<std::string> tmp_stack;
		std::copy(stack.begin(), stack.end(), std::back_inserter(tmp_stack));
		stack.clear();

		std::cout << "----<" << symbol << ">----" << std::endl;
		std::for_each(tmp_stack.begin(), tmp_stack.end(), [&](std::string s){
			std::vector<std::string> tmp_stack_2 = tokenize(s, symbol);
			std::copy(tmp_stack_2.begin(), tmp_stack_2.end(), std::back_inserter(stack));
		});
		std::for_each(stack.begin(), stack.end(), [&](std::string p){
			std::cout << p << "~";
		});
		std::cout << std::endl;
	});
}

Parser::bad_rule::bad_rule(const char* what_arg) : std::runtime_error(what_arg) {}
Parser::bad_rule::~bad_rule() {}
