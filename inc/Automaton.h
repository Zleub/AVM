#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>

#include <utils.h>
#include <Color.h>

class ACallable {
public:
	virtual ~ACallable(void) {};

	virtual int operator()(std::string) = 0;
	virtual std::string toString(void) = 0;
	virtual std::string toString(int indent);
	// virtual void setString(std::string) = 0;
};

class Automaton : public ACallable {
private:
	std::string	cmp;

public:
	Automaton * truthy = NULL;
	Automaton * falsy = NULL;

	Automaton(std::string);
	~Automaton();

	int			operator()(std::string);
	std::string	toString(void);
	std::string	toString(int indent);
};

#endif
