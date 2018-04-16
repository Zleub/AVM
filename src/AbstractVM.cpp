#include <AbstractVM.h>

AbstractVM::AbstractVM(int ac, char *arg[]) {
	struct s_opt opts = { false, false, 0, 0 };

	for (int i = 0; i < ac; i++) {
		std::string _arg(arg[i]);

		if (_arg == "--grammar_file" || _arg == "-gmr")
			opts.grammar_file = arg[i + 1];
		else if (_arg == "--input_file" || _arg == "-in")
			opts.input_file = arg[i + 1];
		else if (_arg == "--no_input")
			opts.no_input = true;
		else if (_arg == "--debug")
			opts.debug = true;
	}

	parser = new Parser(opts);
	 // automaton = new Automaton("Hello");

	if (opts.debug)
		std::cout << "---- Parser ----" << std::endl << parser->toString() << std::endl;

	if (opts.input_file) {
		std::cout << "file: " << opts.input_file << std::endl;

		std::string line;
		std::ifstream f(opts.input_file);
		if (f.is_open()) {
			while (!f.eof()) {
				getline(f, line);
				std::cout << (*parser)(line) << std::endl;
			}
			f.close();
			if ( 0 != f.eof() ) {
				std::cout << Color::start(Color::GREEN) << "File done" << Color::end() << std::endl;
			}
		}
		else {
			std::cout << Color::start(Color::YELLOW) << "File error" << Color::end() << std::endl;
			std::cout << Color::start(Color::BLUE) << ">> " << Color::end() << opts.input_file << std::endl;
			std::cout << ((*parser)(opts.input_file) ? "true" : "false") << std::endl;
		}
	}
	else {
		int ret = 1;
		std::string s;

		while (s != ";;") {
			getline(std::cin, s);
			std::cout << Color::start(Color::BLUE) << ">> " << Color::end() << s << std::endl;
			ret = (*parser)(s);
			std::cout << "[" << (ret ? "true" : "false") << "] " << s << std::endl;
		}
	}
}

AbstractVM::~AbstractVM() {
	delete parser;
}

IOperand const * AbstractVM::createOperand( eOperandType type, std::string const & value ) const {
	return (this->*create_array[type])(value);
}

IOperand const * AbstractVM::createInt8( std::string const & value ) const {
	return new Operand<Int8>(value);
}

IOperand const * AbstractVM::createInt16( std::string const & value ) const {
	return new Operand<Int16>(value);
}

IOperand const * AbstractVM::createInt32( std::string const & value ) const {
	return new Operand<Int32>(value);
}

IOperand const * AbstractVM::createFloat( std::string const & value ) const {
	return new Operand<Float>(value);
}

IOperand const * AbstractVM::createDouble( std::string const & value ) const {
	return new Operand<Double>(value);
}

void AbstractVM::push(IOperand const * operand) {
	push_front(operand);
}

IOperand const * AbstractVM::pop(void) {
	if (size() < 1) {
		throw stack_empty("Stack Empty");
	}

	IOperand const * v = *begin();

	pop_front();
	return v;
}

void AbstractVM::dump(void) const {
	std::cout << toString();
}

std::string AbstractVM::toString(void) const {
	std::stringstream s;

	s << "---- AbstractVM ----" << std::endl;
	std::for_each(begin(), end(), [&s](IOperand const *v) {
		switch (v->getType()) {
			case Int8: s << "Operand<Int8> "; break;
			case Int16: s << "Operand<Int16> "; break;
			case Int32: s << "Operand<Int32> "; break;
			case Float: s << "Operand<Float> "; break;
			case Double: s << "Operand<Double> "; break;
			default: s << "Not a enum value"; break;
		}

		s << v->toString() << std::endl;
	});

	return s.str();
}

void AbstractVM::do_operation(Operation op) {
	try {
		return (this->*operation_array[op])();
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void AbstractVM::add(void) {
	IOperand const *a = pop();
	IOperand const *b = pop();
	push(*a + *b);
}
void AbstractVM::sub(void) {
	IOperand const *a = pop();
	IOperand const *b = pop();
	push(*a - *b);
}
void AbstractVM::mul(void) {
	IOperand const *a = pop();
	IOperand const *b = pop();
	push(*a * *b);
}
void AbstractVM::div(void) {
	IOperand const *a = pop();
	IOperand const *b = pop();
	push(*a / *b);
}
void AbstractVM::mod(void) {
	IOperand const *a = pop();
	IOperand const *b = pop();
	push(*a % *b);
}

AbstractVM::stack_empty::stack_empty(const char* what_arg) : std::runtime_error(what_arg) {}
AbstractVM::stack_empty::~stack_empty() {}
