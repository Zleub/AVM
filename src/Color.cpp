//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T17:11:48+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-03T17:30:35+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <Color.h>

Color::Color() {}
Color::~Color() {}

std::string Color::start(Colors i) {
	if (i == DEFAULT)
		return "\e[0m";
	else {
		std::stringstream s;

		s << "\e[38;5;" << i << "m";
		return s.str();
	}

}
std::string Color::end(void) {
	return "\e[0m";
}
