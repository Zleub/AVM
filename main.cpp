//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <zleub> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:17:02+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-05T19:10:06+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

// #include <AbstractVM.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

int is_equal(std::string a, std::string b) {
	return a == b;
}

class Automaton {
private:
	/* data */

public:
	typedef int (*t_pred)(std::string, std::string);

	class State {
	public:
		std::string l;
		t_pred pred;

		Automaton::State * left;
		Automaton::State * right;
		int operator()(std::string w) {
			return pred(l, w);
		};

		State(std::string l, t_pred pred = is_equal) : l(l);
		virtual ~State();
	};

	Automaton();
	virtual ~Automaton ();
};

Automaton::Automaton() {};
Automaton::~Automaton() {};

Automaton::State::State(t_pred pred) : pred(pred) {}
Automaton::State::~State() {}

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	// AbstractVM avm(av[1]);
	Automaton t;

	Automaton::State A;
	A.lex = "A";
	A.left = new State()

	return (0);
}
