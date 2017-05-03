//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T17:11:01+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-03T18:37:06+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <string>
#include <sstream>

enum Colors {
	DEFAULT,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN
};

class Color {
public:
	Color();
	~Color();

	static std::string start(Colors i);
	static std::string end(void);
};
