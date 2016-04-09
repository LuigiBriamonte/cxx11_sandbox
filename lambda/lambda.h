//============================================================================
// Name        : C++11 - lambda
// Author      : Luigi Briamonte
// Version     :
//============================================================================

#include <iostream>       // std::cout
#include <array>          // std::array
#include <algorithm>      // for_each, sort
#include <iterator>       //

class Car {
public:
	explicit Car(std::string p_name, uint16_t p_quantity) : m_name(p_name), m_quantity(p_quantity)
	{}

	~Car() {}

	friend std::ostream& operator<< (std::ostream& os, const Car& obj)
	{
		return os << "name = " << obj.m_name << ", quantity = " << obj.m_quantity << std::endl;
	}

	std::string getName() const { return m_name; }
	uint16_t getQuantity() const { return m_quantity; }
private:
	std::string m_name;
	uint16_t m_quantity;
};

//bool myfunction (int i,int j) { return (i<j); }
//
//struct myclass {
//  bool operator() (int i,int j) { return (i<j);}
//} myobject;

auto sortByQuantity = [](const Car p_car1, const Car p_car2) {
	  return (p_car1.getQuantity() < p_car2.getQuantity() );
};

auto printCar = [](const Car p_car1, const Car p_car2) {
	std::cout << "printCar" << std::endl;
	std::cout << "\tCar1 : " << p_car1 << "\tCar2 : " << p_car2;
		};

using RandomAccessIterator = std::random_access_iterator_tag;

template<typename RandomAccessIterator, typename Compare>
void myCustomLoop(RandomAccessIterator first, RandomAccessIterator last, Compare fn = printCar)
{
	static RandomAccessIterator curr = first;
	while(curr != last)
	{
		RandomAccessIterator next = std::next(curr);
		if(next != last)
		{
			std::cout << "Curr : " << *curr;
			std::cout << "Next : " << *next;

			fn(*curr, *next);
		}
		std::advance(curr, 1);
	}
}

int main_lambda ()
{
  std::array<Car, 3> l_MyObjs = { Car{"Ferrari", 1}, Car{"Lamborghini", 3}, Car{"BMW", 2} };

  for (auto x: l_MyObjs) std::cout << ' ' << x;
  std::cout << '\n';

  std::for_each(l_MyObjs.begin(), l_MyObjs.end(), [](Car& p_car) {
	std::cout << p_car;
  } );
  std::cout << '\n';


  std::cout << "sorted by name in an ascending order" << std::endl;
  std::sort(l_MyObjs.begin(), l_MyObjs.end(), [](const Car p_car1, const Car p_car2) -> bool {
	  return (p_car1.getName().compare(p_car2.getName()) < 0);
  }  );
  for (auto x: l_MyObjs) std::cout << ' ' << x;
  std::cout << '\n';


  std::cout << "sorted by quantity in an ascending order" << std::endl;
  std::sort(l_MyObjs.begin(), l_MyObjs.end(), sortByQuantity);

  for (auto x: l_MyObjs) std::cout << ' ' << x;
  std::cout << '\n';

  myCustomLoop<decltype(l_MyObjs.begin()), decltype(printCar)>(l_MyObjs.begin(), l_MyObjs.end());

  return 0;
}
