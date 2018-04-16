#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>

#include <Automaton.h>

class Parser : public ACallable {
public:
	class bad_rule : public std::runtime_error {
	public:
		bad_rule(const char* what_arg);
		virtual ~bad_rule();
	};

	Parser(struct s_opt);
	virtual ~Parser();

	void		load(std::string rule);
	int			operator()(std::string line);
	std::string	toString(void);
private:
	Automaton * start;
	Automaton ** next;

	std::map<std::string, Automaton *> automatonMap;

	void push(std::string);
	int symbols(std::string);
};
