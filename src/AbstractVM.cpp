//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <zleub> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:56:06+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-03T18:37:58+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <Color.h>
#include <AbstractVM.h>

AbstractVM::AbstractVM(char *arg) {
	parser = new Parser("AVM.gmr");

	std::cout << "---- Parser ----" << std::endl
		<< parser->toString();

	if (arg) {
		std::cout << "file: " << arg << std::endl;

		std::string line;
		std::ifstream f(arg);
		if (f.is_open()) {
			while (!f.eof()) {
				getline(f, line);
				parser->process(line);
			}
			f.close();
			if ( 0 != f.eof() ) {
				std::cout << Color::start(GREEN) << "File done" << Color::end() << std::endl;
			}
		}
		else {
			std::cout << Color::start(RED) << "File error" << Color::end() << std::endl;
		}
	}
	else {
		std::string s;

		while (s != ";;") {
			getline(std::cin, s);
			parser->process(s);
		}
	}
}
AbstractVM::~AbstractVM() {}

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

std::string const & AbstractVM::toString(void) const {
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

	return *new std::string(s.str());
}

void AbstractVM::do_operation(operationEnum op) {
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
