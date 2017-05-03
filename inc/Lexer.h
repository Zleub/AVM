//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-03T18:26:49+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-03T18:28:38+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

class Lexer.h {
public:
	class Token {
		std::String operand;
		operationEnum operation;
	}

	Lexer();
	~Lexer();

	static tokenize(std::string line);
}
