//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T15:26:42+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-05T20:16:01+02:00
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

	if (i != -1) {
		std::vector<std::string> A = tokenize(s.substr(0, i), sep);
		std::for_each(A.begin(), A.end(), [&](std::string s){
			stack.push_back(s);
		});
		std::vector<std::string> B = tokenize(s.substr(i + 1, -1), sep);
		std::for_each(B.begin(), B.end(), [&](std::string s){
			stack.push_back(s);
		});
	}
	else
		stack.push_back(s);
	return stack;
}

Parser::Parser(void) : anonyme_count(0) {}
Parser::Parser(std::string grammar_file) : anonyme_count(0) {
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
			_expand_group();
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

void Parser::process(std::string line) {
	std::cout << Color::start(CYAN) << "~ line: " << Color::end() << line << std::endl;

	std::for_each(rules.begin(), rules.end(), [line](Rule * r) {
		std::smatch sm;
		std::cout << r->name << "\t" << r->text << std::endl;
	});
}

void Parser::_load(std::string rule) {
	std::smatch sm;

	std::regex_match(rule, sm, parse_rule);
	if (sm.size() != 3)
		throw bad_rule(("Not a valid rule: " + Color::start(RED) + rule + Color::end()).c_str());

	std::cout << Color::start(GREEN) << "New rule: " << Color::end() << rule << std::endl;
	rules.push_back( new Rule(sm[1], sm[2]) );
}

Parser::Rule * Parser::_match_group(Rule * r, char begin, char end) {
	std::string s1, s2, s3;
	std::tie(s1, s2, s3) = get_group(r->text, begin, end);
	if (s1 != r->text)
	{
		std::string name = "ANON" + std::to_string(anonyme_count);
		std::stringstream s;

		s << begin << s2 << end;

		std::string m = s.str();
		m = std::regex_replace(m, std::regex("\\\\"), "\\\\");
		m = std::regex_replace(m, std::regex("\\["), "\\[");
		m = std::regex_replace(m, std::regex("\\]"), "\\]");

		r->text = std::regex_replace(r->text, std::regex(m + "[*?+]?"), " " + name + " ");

		Rule * _ = new Rule(name, s2);
		if (s3.find("?") == 1)
			_->quantifier = ZERO_OR_ONE;
		if (s3.find("*") == 1)
			_->quantifier = ZERO_OR_MORE;
		if (s3.find("+") == 1)
			_->quantifier = ONE_OR_MORE;

		anonyme_count += 1;
		return _;
	}

	return NULL;
}

Parser::Rule * Parser::_match_separator(Rule * r, char separator) {
	// std::string s1, s2;
	// std::tie(s1, s2) = get_symbol(r->text, separator);

	std::stringstream s;
	s << separator;
	std::vector<std::string> v = tokenize(r->text, s.str());
	if (v[0] != r->text) {
		std::for_each( v.begin(), v.end(), [](std::string s){
			// std::cout << std::regex_match(s, std::regex("\\s*\\S*\\s*")) << std::endl;
			if ( !std::regex_match(s, std::regex("\\s*\\S*\\s*")) ) {
				std::cout << s << std::endl;
				std::smatch sm;
				std::regex_match(s, sm, std::regex("\\s*(.*?)\\s*"));
				std::for_each(sm.begin(), sm.end(), [](std::string s){
					std::cout << Color::start(CYAN) << "<" << s << ">" << Color::end() << std::endl;
				});

			// 	std::cout << "<" << s1 << ">" << std::endl;
			// 	std::string name = "ANON" + std::to_string(anonyme_count);
			//
			// 	r->text = std::regex_replace(r->text, std::regex(s1 + "[*?+]?"), " " + name + " ");
			//
			// 	Rule * _ = new Rule(name, s1);
			// 	if (s2.find("?") == 1)
			// 		_->quantifier = ZERO_OR_ONE;
			// 	if (s2.find("*") == 1)
			// 		_->quantifier = ZERO_OR_MORE;
			// 	if (s2.find("+") == 1)
			// 		_->quantifier = ONE_OR_MORE;
			//
			// 	anonyme_count += 1;
			// 	return _;
			}
		});


	}
	return NULL;
}

void Parser::_expand_group(void) {
	std::vector<Rule *> new_rules;

	std::for_each( rules.begin(), rules.end(), [&](Rule * r){
		std::for_each( groups.begin(), groups.end(), [&](std::tuple<char, char> g) {
			Rule * _ = _match_group(r, std::get<0>(g), std::get<1>(g));
			if (_)
				new_rules.push_back(_);
		});
	});

	if (!new_rules.empty()) {
		std::for_each(new_rules.begin(), new_rules.end(), [&](Rule * r) {
			rules.push_back(r);
		});
		_expand_group();
	}
	else
		_expand_separator();
}

void Parser::_expand_separator(void) {
	std::vector<Rule *> new_rules;

	std::for_each( rules.begin(), rules.end(), [&](Rule * r){
		std::for_each( separators.begin(), separators.end(), [&](char c) {
			Rule * _ = _match_separator(r, c);
			if (_) {
				// std::smatch sm;
				// std::regex_search(r->text, sm, std::regex("\\|\\s*([^|]*)\\s*\\|"));
				// std::for_each(sm.begin(), sm.end(), [](std::string s) {
				// 	std::cout << Color::start(CYAN) << s << Color::end() << std::endl;
				// });

				std::cout << _ << std::endl;

				new_rules.push_back(_);
			}
		});
	});

	if (!new_rules.empty()) {
		std::for_each(new_rules.begin(), new_rules.end(), [&](Rule * r) {
			rules.push_back(r);
		});
		_expand_separator();
	}
}

std::string Parser::toString(void) {
	std::stringstream s;

	std::for_each( rules.begin(), rules.end(), [&s](Rule *r){
		std::string quantifier;

		switch (r->quantifier) {
			case NONE: quantifier = " "; break;
			case ZERO_OR_ONE: quantifier = "?"; break;
			case ZERO_OR_MORE: quantifier = "*"; break;
			case ONE_OR_MORE: quantifier = "+"; break;
			default: quantifier = ""; break;
		}

		s << "[" << quantifier << "] " << r->name << ": " << r->text << std::endl;
	});

	return s.str();
}

Parser::bad_rule::bad_rule(const char* what_arg) : std::runtime_error(what_arg) {}
Parser::bad_rule::~bad_rule() {}

Parser::Rule::Rule(std::string name, std::string regex, Quantifiers q) :
	name(name), text(regex), quantifier(q) {}

Parser::Rule::~Rule() {}

// struct Parser::Result Parser::Rule::exec(std::string s) {
// 	(void)s;
//
// 	// std::cout << Color::start(RED) << "exec[" << name << "]" << Color::end() << std::endl;
//
// 	// std::streambuf sb(text);
//
// 	// std::cout << sb << std::endl;
//
// 	return ((struct Parser::Result){ .res = KO });
// }
