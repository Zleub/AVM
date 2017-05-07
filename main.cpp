//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <zleub> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:17:02+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-07T16:33:06+02:00
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
	return (0);
}
