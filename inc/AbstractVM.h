#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

#include <utils.h>
#include <Color.h>
#include <Operand.h>
#include <Parser.h>
#include <Automaton.h>

class AbstractVM : public std::deque<IOperand const *> {
public:
	enum Operation {
		ADD,
		SUB,
		MUL,
		DIV,
		MOD
	};

	class stack_empty : public std::runtime_error {
	public:
		stack_empty(const char* what_arg);
		virtual ~stack_empty();
	};

	AbstractVM(int ac, char *arg[]);
	virtual ~AbstractVM();

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	void push(IOperand const *);
	IOperand const * pop(void);
	void dump(void) const;
	void do_operation(Operation op);

	std::string toString( void ) const;

private:
	Parser *parser;
	// Automaton *automaton;

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
