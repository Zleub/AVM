//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T17:11:48+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-06T17:41:07+02:00
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

std::string Color::bold(void) {
	return "\e[1m";
}

std::string Color::dim(void) {
	return "\e[2m";
}

std::string Color::underline(void) {
	return "\e[4m";
}

std::string Color::blink(void) {
	return "\e[5m";
}

std::string Color::reverse(void) {
	return "\e[7m";
}

std::string Color::hidden(void) {
	return "\e[8m";
}
