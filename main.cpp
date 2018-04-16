#include <AbstractVM.h>

int is_equal(std::string a, std::string b) {
	return a == b;
}

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	AbstractVM avm(ac, av);

	// Automaton a("Hello");

	// std::cout << a.toString() << std::endl;
	// std::cout << a("Hello world !") << std::endl;
	return (0);
}
