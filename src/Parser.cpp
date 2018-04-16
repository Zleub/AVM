#include <Parser.h>

std::string &trim(std::string &s);

std::string ACallable::toString(int indent) {
	(void)indent;
	return toString();
}

Parser::Parser(struct s_opt opts) : start(NULL) {
	if (!opts.grammar_file) {
		std::string line;

		while (getline(std::cin, line)) {
			load(line);
		}
	}
	else {
		std::ifstream f(opts.grammar_file);
		std::string line;

		if (f.is_open()) {
			while (!f.eof()) {
				getline(f, line);
				if (line != "")
					load(line);
			}
			f.close();
			if ( 0 != f.eof() ) {
				if (opts.debug)
					std::cout << Color::start(Color::GREEN) << "File done" << Color::end() << std::endl;
			}
		}
		else {
			// std::cout << Color::start(Color::RED) << "File error" << Color::end() << std::endl;
			load(opts.grammar_file);
		}
	}
}

Parser::~Parser() {
	for (std::pair<std::string, Automaton*> e: automatonMap) {
		delete e.second;
		automatonMap.erase(e.first);
	}
}

void Parser::push(std::string s) {
	Automaton * _ = new Automaton(trim(s));

	// if (!next)
	// 	next = &start;

	*next = _;
	automatonMap.insert( std::pair<std::string, Automaton *>(s, _));
}

int Parser::symbols(std::string expr) {
	int ret = 0;

	std::vector< std::string > symbols = {
		"\\*", "\\-", ",", "\\|", "=", ";", "\\."
	};

	std::for_each(symbols.begin(), symbols.end(), [&](const std::string& p ) {
		std::string s = "(.*?)" + p + "(.+)";
		std::smatch m;
		std::regex r(s);

		while (std::regex_search(expr.cbegin(), expr.cend(), m, r))
		{
			// for (size_t i = 1; i < m.size(); i++)
			// 	std::cout << "m[" << i << "] " << m[i] << std::endl;

			this->symbols( m[1] );

			if (p == "\\|")
				next = &((*next)->falsy);
			else if (p == "=") {
				start = (*next)->truthy;
			}
			else
				next = &((*next)->truthy);

			// std::cout << m[1] << std::endl;
			expr = m[2];
			ret = 1;
		}
	});

	push(expr);
	return ret;
}

void Parser::load(std::string rule) {
	std::cout << Color::start(Color::Color::GREEN) << "Parser load : " << Color::end() << rule << std::endl;

	// std::vector< std::pair<std::string, std::string> > pairs = {
	// 	{ "'", "'" },
	// 	{ "\"", "\"" },
	// 	{ "\\(\\*", "\\*\\)" },
	// 	{ "\\(", "\\)" },
	// 	{ "\\[", "\\]" },
	// 	{ "\\{", "\\}" },
	// 	{ "\\?", "\\?" }
	// };

	// std::smatch m;
	// std::regex e ("(\\w+)\\s+:=\\s+(.+)");

	// try {
	// 	std::regex_search(rule, m, e);
	// } catch (std::exception e) {
	// 	std::cout << e.what() << std::endl;
	// }

	// if (m.empty()) {
	// 	std::cout << "No match" << std::endl;
		next = (!start ? &start : next);
		symbols(rule);
	// }
	// else if (m.size() == 3) {
	// 	std::string name = m[1];
	// 	std::string expr = m[2];
	//
	//
	// 	// automatonMap.insert( std::pair<std::string, Automaton*>(name, new Automaton(name)) );
	// 	std::for_each(pairs.begin(), pairs.end(), [&](const std::pair<std::string, std::string>& p ) {
	// 		std::string::const_iterator text_iter = expr.cbegin();
	// 		std::string s = "(" + p.first + ")(\\w+)(" + p.second + ")";
	// 		std::smatch m;
	// 		// std::cout << "regex: " << s << std::endl;
	// 		std::regex r(s);
	//
	// 		(void)p;
	// 		while (std::regex_search(text_iter, expr.cend(), m, r))
	// 		{
	// 			// int count = m.size();
	// 			// Alloc pointer array based on count * sizeof(mystruct).
	// 			// for ( std::cmatch::iterator group = m.begin(); group != m.end(); ++group )
	// 			// {
	// 				// If you uses grouping in your search here you can access each group
	// 			// }
	//
	// 			// std::cout << std::string(m[0].first, m[0].second) << std::endl;
	// 			text_iter = m[0].second;
	// 		}
	// 	});
	//
	// 	symbols(expr);
	// 	std::cout << toString() << std::endl;
	// }
}

int Parser::operator()(std::string s) {
	if (!start)
		std::cout << "Parser::operator(), should call an entry point" << std::endl;
	else
		return (*start)(s);
	return 0;
}

std::string Parser::toString(void) {
	std::stringstream ss;

	ss << "start: " << (start ? start->toString(0) : "null");
	return ss.str();
}

Parser::bad_rule::bad_rule(const char* what_arg) : std::runtime_error(what_arg) {}
Parser::bad_rule::~bad_rule() {}
