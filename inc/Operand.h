//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-02T12:43:08+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-03T15:11:01+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <IOperand.h>
#include <math.h>

template<eOperandType T>
class Operand : public IOperand {
public:
	std::string const & value;

	Operand(std::string const & value);
	Operand(Operand<T> const & operand);
	Operand<T> & operator=(Operand<T> const & rhs);
	virtual ~Operand();

	int getPrecision( void ) const;
	eOperandType getType( void ) const;

	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;

	std::string const & toString( void ) const;

	class division_by_zero : public std::runtime_error {
	public:
		division_by_zero(const char* what_arg);
		virtual ~division_by_zero();
	};

private:
	IOperand const * result(double r, int type) const;
};

template<eOperandType T>
Operand<T>::Operand(std::string const & value) : value(value) {}
template<eOperandType T>
Operand<T>::Operand(Operand<T> const & operand) : value(operand.value) {}

template<eOperandType T>
Operand<T> & Operand<T>::operator=(Operand<T> const & rhs) {
	value = rhs.toString();
}

template<eOperandType T>
Operand<T>::~Operand() {}

template<eOperandType T>
int Operand<T>::getPrecision(void) const {
	return (T);
}
template<eOperandType T>
eOperandType Operand<T>::getType(void) const {
	return (T);
}

template<eOperandType T>
IOperand const * Operand<T>::result(double r, int type) const {
	std::stringstream s;

	s << r;
	switch (type) {
		case Int8: return new Operand<Int8>(*new std::string(s.str())); break;
		case Int16: return new Operand<Int16>(*new std::string(s.str())); break;
		case Int32: return new Operand<Int32>(*new std::string(s.str())); break;
		case Float: return new Operand<Float>(*new std::string(s.str())); break;
		case Double: return new Operand<Double>(*new std::string(s.str())); break;
		default: return NULL; break;
	}
}

template<eOperandType T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const {
	double i = stof(value) + stof(rhs.toString());
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}

template<eOperandType T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const {
	double i = stof(value) - stof(rhs.toString());
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());}

template<eOperandType T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const {
	double i = stof(value) * stof(rhs.toString());
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}

template <>
inline IOperand const * Operand<Float>::operator/( IOperand const & rhs ) const {
	if (stof(rhs.toString()) == .0)
		throw division_by_zero("Division by zero");

	double i = stof(value) / stof(rhs.toString());
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}

template <>
inline IOperand const * Operand<Double>::operator/( IOperand const & rhs ) const {
	if (stof(rhs.toString()) == .0)
		throw division_by_zero("Division by zero");

	double i = stof(value) / stof(rhs.toString());
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}

template<eOperandType T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const {
	double i = stof(value) / stof(rhs.toString());
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}

template<eOperandType T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const {
	double i = fmod(stof(value), stof(rhs.toString()));
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}
template <>
inline IOperand const * Operand<Float>::operator%( IOperand const & rhs ) const {
	if (stof(rhs.toString()) == .0)
		throw division_by_zero("Division by zero");

	double i = fmod(stof(value), stof(rhs.toString()));
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}
template <>
inline IOperand const * Operand<Double>::operator%( IOperand const & rhs ) const {
	if (stof(rhs.toString()) == .0)
		throw division_by_zero("Division by zero");

	double i = fmod(stof(value), stof(rhs.toString()));
	return result(i, (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision());
}

template<eOperandType T>
std::string const & Operand<T>::toString( void ) const {
	return value;
}

template<eOperandType T>
Operand<T>::division_by_zero::division_by_zero(const char* what_arg) : std::runtime_error(what_arg) {}
template<eOperandType T>
Operand<T>::division_by_zero::~division_by_zero() {}
