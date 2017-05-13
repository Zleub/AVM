//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-07T16:06:52+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-09T19:23:56+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <Automaton.h>

Automaton::Automaton(std::string name) : name(name), start(NULL) {};
Automaton::~Automaton() {};

int Automaton::operator()(std::string s) {
	std::string input = s;

	prev = NULL;
	current = start;
	index = 0;

	std::cout << std::endl << "---- " << Color::start(CYAN) << "New run " << Color::bold() << name << Color::end() << " ----" << std::endl;
	std::cout << input << std::endl;

	while (s.find_first_of(" \t") == 0) {
		s = s.substr(1, -1);
		index += 1;
	}

	while ( current ) {
		current = transition(&s, current);
	}

	bool is_accepted = false;

	std::for_each( accept_states.begin(), accept_states.end(), [&](ACallable * s) {
		if (s == prev && index == input.length())
			is_accepted = true;
	});

	if (is_accepted) {
		std::cout << Color::start(GREEN) << "Final State" << Color::end() << std::endl;
		return 1;
	}
	else {
		std::cout << Color::start(RED) << "Final State" << Color::end() << std::endl;
		std::cout << input << std::endl;

		std::stringstream padding;
		for (size_t i = 0; i < index; i++) {
			padding << " " ;
		}

		ACallable * out = prev == NULL ? start : prev->truthy;

		std::stringstream ss;
		ss << padding.str() << Color::bold() << Color::start(ORANGE) << "^" << Color::end() << " expected: " ;
		ss << Color::underline() << out->toString() << Color::end() << std::endl;
		while (out) {
			out = out->falsy;
			if (out)
				ss << padding.str() << "            " << Color::underline() << out->toString() << Color::end() << std::endl;
		}

		std::cout << ss.str() ;
		return 0;
	}
}

ACallable * Automaton::transition(std::string * s, ACallable * current)
{
	std::string part = (*s).substr(0, current->toString().length());

	if ((*current)(part)) {
		*s = (*s).substr(current->toString().length(), -1);
		while ((*s).find_first_of(" \t") == 0) {
			*s = (*s).substr(1, -1);
			index += 1;
		}
		index += part.length();
		prev = current;
		return current->truthy;
	}
	else {
		return current->falsy;
	}
}

std::string Automaton::toString(void) {
	std::stringstream ss;

	ss << Color::start(CYAN) << name << Color::end() << std::endl;
	if (start)
		ss << Color::start(GREEN) << "start: " << start->toString() << Color::end() << std::endl;
	else
		ss << Color::start(RED) << "No start !" << Color::end() << std::endl;
	std::for_each(states.begin(), states.end(), [&](ACallable * s) {
		// ss << "\t" << "    " << " T " << " F " << std::endl;
		ss << "\t" << s->toString() << " ? " ;
		if (s->truthy)
			ss << s->truthy->toString();
		else
			ss << "NULL";
		ss << " : ";
		if (s->falsy)
			ss << s->falsy->toString();
		else
			ss << "NULL";
		ss << std::endl;
	});
	return ss.str();
}

void Automaton::setString(std::string s) {
	name = s;
}

Automaton::State::State(std::string l) : l(l) {}
Automaton::State::~State() {}

std::string Automaton::State::toString(void) {
	return l;
}

void Automaton::State::setString(std::string s) {
	l = s;
}
