//============================================================================
// Name        : C++11
// Author      : Luigi Briamonte
// Version     :
//============================================================================

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

class Person
{
public:
  enum class KIDS
  {
	  ONE = 1,
	  TWO
  };
  public:
  explicit Person() : Person(33, KIDS::TWO)
  {}

  Person(int p_age, KIDS p_nbKids = KIDS::ONE) : m_age(p_age), m_kids_number(p_nbKids)
  {  }

  virtual ~Person() {}

  Person& operator= (const Person& other) = delete;

  template<int weight>
  constexpr void setWeight()
  {
	  static_assert(weight == 75, "expected weight == 75");
  }

  std::string toString() const
  {
	  stringstream l_str;
	  l_str << "Age : " << m_age;
	  l_str << ", Weight : " << m_weight;
	  l_str << ", Kids : " << (int)m_kids_number;
	  return l_str.str();
  }

  friend std::ostream& operator<<(std::ostream& os, const Person& p_obj)
  {
	  return os << p_obj.toString();
  }

private:
  static constexpr int m_weight = 75;
  int m_age;
  const KIDS m_kids_number;
};

namespace luigi {
	namespace constants {  // present constants as variable templates (C++14)
		static int staticValue = 1;

		template <typename T>
		constexpr T getValue()
		{
			return 1.4;
		}

		constexpr int constexprValue = 1234;
	}

	namespace Unit {
		Person operator "" _aged(long double value1) {
		  return Person((int)value1);
		}
	}
}

int main_constexpr() {
	Person a;
	Person b(12, Person::KIDS::TWO);

	cout << a << endl;
	cout << b << endl;

	b.setWeight<75>();

	// =====================================================================
	//    constants
	// =====================================================================
	using namespace luigi::constants;
	cout << "luigi::constants::staticValue = " << staticValue << endl;
	cout << "luigi::constants::getValue<double> = " << getValue<double>() << endl;
	cout << "luigi::constants::getValue<int> = " << getValue<int>() << endl;

	cout << "luigi::constants::constexprValue = " << constexprValue << endl;

//	warning at compile time since constexprValue is read only
//	constexprValue = 9876;
//	cout << "luigi::constants::constexprValue = " << constexprValue << endl;

	// =====================================================================
	//    uniform initialization
	// =====================================================================
	// warning: narrowing conversion of ‘pi’ from ‘double’ to ‘int’ inside
    double pi = 3.14;
    int pi_2 = {pi};  // not detected without {}-initialization
    cout << "pi = " << pi << ", pi_2 = " << pi_2 << endl;

	// =====================================================================
	//    user-defined literals
	// =====================================================================
    using namespace luigi::Unit;
    cout << "user-defined literals = " << 35.0_aged << endl;
	return 0;

}
