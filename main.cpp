//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <zleub> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:17:02+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-07T01:34:00+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

// #include <AbstractVM.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>

#include <Color.h>

int is_equal(std::string a, std::string b) {
	return a == b;
}

class Automaton {
public:
	class State {
	public:
		std::string l;

		Automaton::State * truthy;
		Automaton::State * falsy;
		int operator()(std::string w) {
			return w == l;
		};

		State(std::string l) ;
		virtual ~State();
	};

	Automaton(std::string="unnamed");
	virtual ~Automaton ();

	std::string name;

	State * start;
	State * prev;
	State * current;

	size_t index;
	std::vector<State *> states;
	std::vector<State *> accept_states;

	void run(std::string);
	State * transition(std::string *, State *);
};

Automaton::Automaton(std::string name) : name(name) {};
Automaton::~Automaton() {};

Automaton::State::State(std::string l) : l(l) {}
Automaton::State::~State() {}

Automaton::State * Automaton::transition(std::string * s, State * current)
{
	std::string part = (*s).substr(0, current->l.length());

	if ((*current)(part)) {
		*s = (*s).substr(current->l.length(), -1);
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

void Automaton::run(std::string s) {
	std::string input = s;

	prev = start;
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

	std::for_each( accept_states.begin(), accept_states.end(), [&](Automaton::State * s) {
		if (s == prev && index == input.length())
			is_accepted = true;
	});

	if (is_accepted) {
		std::cout << Color::start(GREEN) << "Final State" << Color::end() << std::endl;
	}
	else {
		std::cout << Color::start(RED) << "Final State" << Color::end() << std::endl;
		std::cout << input << std::endl;

		std::stringstream padding;
		for (size_t i = 0; i < index; i++) {
			padding << " " ;
		}

		State * out = prev == start ? prev : prev->truthy;

		std::stringstream ss;
		ss << padding.str() << Color::bold() << Color::start(ORANGE) << "^" << Color::end() << " expected: " ;
		ss << Color::underline() << out->l << Color::end() << std::endl;
		while (out) {
			out = out->falsy;
			if (out)
				ss << padding.str() << "            " << Color::underline() << out->l << Color::end() << std::endl;
		}

		std::cout << ss.str() ;
	}
}

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	Automaton t("test");

	Automaton::State * A = new Automaton::State("Arno");
	Automaton::State * B = new Automaton::State("Arnaud");
	Automaton::State * C = new Automaton::State("est un");
	Automaton::State * D = new Automaton::State("bouffon");
	Automaton::State * E = new Automaton::State("boloss");
	Automaton::State * F = new Automaton::State(",");

	// Arno|Arnaud est un bouffon|boloss [, bouffon|boloss]*

	A->truthy = C;
	A->falsy = B;

	B->truthy = C;
	B->falsy = NULL;

	C->truthy = D;
	C->falsy = NULL;

	D->truthy = F;
	D->falsy = E;

	E->truthy = F;
	E->falsy = NULL;

	F->truthy = D;
	F->falsy = NULL;


	t.start = A;

	t.states.push_back(A);
	t.states.push_back(B);
	t.states.push_back(C);
	t.states.push_back(D);
	t.states.push_back(E);
	t.states.push_back(F);

	t.accept_states.push_back(A);
	// t.accept_states.push_back(B);
	t.accept_states.push_back(D);
	t.accept_states.push_back(E);
	// t.accept_states.push_back(F);

	std::for_each(t.states.begin(), t.states.end(), [&](Automaton::State * s) {
		std::cout << (std::find(t.accept_states.begin(), t.accept_states.end(), s) == t.accept_states.end() ? "X" : "√")
			<< " " << s << " " << s->l << std::endl;
	});

	t.run("Arno est un boloss");
	// t.run("Arno est un bouffon");
	// t.run("Arnaud est un boloss");
	// t.run("Arnaud est un bouffon");
	// t.run("Arno     est un boloss   ");
	// t.run("          Arno     est un boloss   ");
	t.run("   Arnaud est un bouffon, boloss");
	t.run("   Arnaud est un boloss, bouffon");
	t.run("   Arnaud est un boloss, boloss");

	t.run("Arnaud mange bouffon");
	t.run("Arnaud est un mongol");
	t.run("   Arnaud mange bouffon");
	t.run("   Arnaud ");
	t.run("   Arnaud est un boloss,");
	t.run("");

	return (0);
}
