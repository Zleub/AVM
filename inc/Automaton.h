//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-07T16:07:15+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-07T16:31:17+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <string>
#include <vector>

#include <Color.h>

class ACallable {
public:
	ACallable * truthy;
	ACallable * falsy;

	virtual ~ACallable(void) {};

	virtual int operator()(std::string) = 0;
	virtual std::string toString(void) = 0;
};

class Automaton : public ACallable {
public:
	class State : public ACallable {
	public:
		std::string l;

		int operator()(std::string w) {
			return w == l;
		};

		State(std::string l) ;
		virtual ~State();

		std::string toString(void);
	};

	Automaton(std::string="unnamed");
	virtual ~Automaton (void);

	std::string name;

	ACallable * start;
	ACallable * prev;
	ACallable * current;

	size_t index;
	std::vector<ACallable *> states;
	std::vector<ACallable *> accept_states;

	int operator()(std::string);
	ACallable * transition(std::string *, ACallable *);
	std::string toString(void);
};

#endif
