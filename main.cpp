//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <zleub> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:17:02+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-15T01:46:50+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <AbstractVM.h>
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <deque>
// #include <vector>

#include <Automaton.h>

int is_equal(std::string a, std::string b) {
	return a == b;
}

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	AbstractVM avm(av[1]);

	// Automaton t("test");
	//
	// Automaton::State * A = new Automaton::State("Arno");
	// Automaton::State * B = new Automaton::State("Arnaud");
	// Automaton::State * C = new Automaton::State("est un");
	// Automaton::State * D = new Automaton::State("bouffon");
	// Automaton::State * E = new Automaton::State("boloss");
	// Automaton::State * F = new Automaton::State(",");
	//
	// // Arno|Arnaud est un bouffon|boloss [, bouffon|boloss]*
	//
	// A->truthy = C;
	// A->falsy = B;
	//
	// B->truthy = C;
	// B->falsy = NULL;
	//
	// C->truthy = D;
	// C->falsy = NULL;
	//
	// D->truthy = F;
	// D->falsy = E;
	//
	// E->truthy = F;
	// E->falsy = NULL;
	//
	// F->truthy = D;
	// F->falsy = NULL;
	//
	//
	// t.start = A;
	//
	// t.states.push_back(A);
	// t.states.push_back(B);
	// t.states.push_back(C);
	// t.states.push_back(D);
	// t.states.push_back(E);
	// t.states.push_back(F);
	//
	// t.accept_states.push_back(A);		// Arno
	// // t.accept_states.push_back(B);	// Arnaud
	// t.accept_states.push_back(D);		// [Arno|Arnaud] est un bouffon
	// t.accept_states.push_back(E);		// [Arno|Arnaud] est un boloss
	// // t.accept_states.push_back(F);
	//
	//
	// std::cout << t.toString() ;
	//
	// t("Arno est un boloss");
	// // t("Arno est un bouffon");
	// // t("Arnaud est un boloss");
	// // t("Arnaud est un bouffon");
	// // t("Arno     est un boloss   ");
	// // t("          Arno     est un boloss   ");
	// t("   Arnaud est un bouffon, boloss");
	// t("   Arnaud est un boloss, bouffon");
	// t("   Arnaud est un boloss, boloss");
	//
	// t("Arnaud mange bouffon");
	// t("Arnaud est un mongol");
	// t("   Arnaud mange bouffon");
	// t("   Arnaud ");
	// t("   Arno ");
	// t("   Arnaud est un boloss,");
	// t("");

	return (0);
}
