//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <zleub> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:17:02+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-02T23:36:50+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <AbstractVM.h>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	AbstractVM avm;

	avm.push(avm.createOperand(Int8, "0"));
	avm.push(avm.createOperand(Float, "0"));
	avm.push(avm.createOperand(Float, "0"));

	avm.do_operation(ADD);
	avm.dump();
	avm.do_operation(MOD);
	avm.dump();

	return (0);
}
