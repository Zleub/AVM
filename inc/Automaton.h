#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>

#include <Color.h>

class ACallable {
public:
	ACallable * truthy = NULL;
	ACallable * falsy = NULL;

	virtual ~ACallable(void) {};

	virtual int operator()(std::string) = 0;
	virtual std::string toString(void) = 0;
	// virtual void setString(std::string) = 0;
};

class Automaton : public ACallable {
private:
	std::string	cmp;

public:
	Automaton(std::string);
	~Automaton();

	int			operator()(std::string);
	std::string	toString();
};

class Parser : public ACallable {
public:
	class bad_rule : public std::runtime_error {
	public:
		bad_rule(const char* what_arg);
		virtual ~bad_rule();
	};

	Parser(void);
	Parser(std::string grammar_file);
	virtual ~Parser();

	void		load(std::string rule);
	int			operator()(std::string line);
	std::string	toString(void);
private:
	std::string acc;

	std::map<std::string, std::vector<Automaton *>> automatonMap;
};

#endif
