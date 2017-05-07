//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T17:11:01+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-07T16:18:16+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <sstream>

enum Colors {
	DEFAULT,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	ORANGE = 202
};

class Color {
public:
	Color();
	~Color();

	static std::string start(Colors i);
	static std::string end(void);
	static std::string bold(void);
	static std::string dim(void);
	static std::string underline(void);
	static std::string blink(void);
	static std::string reverse(void);
	static std::string hidden(void);
};

#endif
