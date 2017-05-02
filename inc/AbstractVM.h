//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <zleub> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:56:38+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-02T23:22:30+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <iostream>
#include <sstream>
#include <deque>
#include <Operand.h>

enum operationEnum {
	ADD,
	SUB,
	MUL,
	DIV,
	MOD
};

class AbstractVM : public std::deque<IOperand const *> {

public:
	AbstractVM();
	virtual ~AbstractVM();

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	void push(IOperand const *);
	IOperand const * pop(void);

	void dump(void) const;

	void do_operation(operationEnum op);

	std::string const & toString( void ) const;

	class stack_empty : public std::runtime_error {
	public:
		stack_empty(const char* what_arg);
		virtual ~stack_empty();
	};

private:
	typedef IOperand const * (AbstractVM::*createPtr)( std::string const & value ) const;

	createPtr create_array[eOperandLen] = {
		&AbstractVM::createInt8,
		&AbstractVM::createInt16,
		&AbstractVM::createInt32,
		&AbstractVM::createFloat,
		&AbstractVM::createDouble
	};

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	typedef void (AbstractVM::*operationPtr)(void) ;


	operationPtr operation_array[5] = {
		&AbstractVM::add,
		&AbstractVM::sub,
		&AbstractVM::mul,
		&AbstractVM::div,
		&AbstractVM::mod
	};

	void add(void) ;
	void sub(void) ;
	void mul(void) ;
	void div(void) ;
	void mod(void) ;
};
