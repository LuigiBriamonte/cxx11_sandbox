//============================================================================
// Name        : C++11 - forwarding constructors
// Author      : Luigi Briamonte
// Version     :
//============================================================================

// refer to http://en.cppreference.com/w/cpp/language/using_declaration for details

#include <iostream>       // std::cout

class Base
{
  public:
    Base( int p_value )    : value(p_value) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;
    Base( void )           : value(1)       { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;
    Base( double p_value ) : value(p_value) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;

    virtual void f( int    ) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;
    void f( void   ) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;
    void f( double ) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;
    void f( short )  { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;

    int getValue(int )    const { return value; }
    int getValue(double ) const { return value; }

  protected:
    int value;         // Base::value is protected
} ;

class Derived: public Base
{
  public:
	using Base::value; // Derived::value is now public in Derived scope. It can be thus accessed as d1.value

    void f( char ) { std::cout << __PRETTY_FUNCTION__ << std::endl; value = 11; } ;  // It adds a new overload to function 'f'.
    void f( int  ) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;              // D::f(int) hides B::f(int) AND
    // all other Base::f method declarations, hence we need to forward Base::f declarations
    // otherwise none all the Base::f class method can be accessed through Derived instance.
    // for instance Derived.f(double) won't compile
    using Base::f ;  // all base class member functions with that name are introduced

    // without the usage of forwarding base class member methods,
    // we could declare the method with the same signature and internally invoke Base class method
    void f( short param) {
    	Base::f(param);
    	std::cout << __PRETTY_FUNCTION__ << std::endl; } ;

    using Base::Base ;  // all base class ctor functions are introduced into Derived scope.
    Derived( char ) : Base(2) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;  // Aggiunge un nuovo costruttore.
    Derived( int  ) : Base(2) { std::cout << __PRETTY_FUNCTION__ << std::endl; } ;  // 'Derived( int  )' hides 'Base::Base( int )'.

    using Base::getValue ;
    int getValue(bool* )    const { return value; }
} ;

int main_fw_constructors ()
{
  Derived d1(1);
  d1.f(10);
  d1.f(double{10.2});
  d1.value = 5;

  std::cout << "d1.value = " << d1.getValue(2) << std::endl;


  Derived d2(double{10.2});

  std::cout << "d2.value = " << d2.getValue(2) << std::endl;

  d2.f(short{8});

  return 0;
}
