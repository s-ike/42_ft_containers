#include <iostream>
#include <array>
#include <vector>
#include "vector.hpp"

template <class T>
void print_container(T& container)
{
	std::cout << "{ ";
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		std::cout <<  *it << ' ';
	std::cout << '}' << std::endl;
}

int main()
{
	{
		// ft::vector<int> v;
		// std::cout << v.size() << std::endl;
		ft::vector<int> v(10, 1) ;
		v[2] = 99 ;
		v.resize(5) ;
		print_container(v);
		v.push_back(42);
		print_container(v);
		std::cout << "capa: " << v.capacity() << std::endl;
	}
	{
		std::array<int, 5> a = {100,2,3,4,5} ;
		ft::vector<int> v( std::begin(a), std::end(a) ) ;
		print_container(v);
	}
	{
		ft::vector<int> v(10, 1);
		ft::vector<int> v2(v);
		v2[1] = 42;
		print_container(v);
		print_container(v2);
	}
	{
		ft::vector<int> v(10, 1);
		ft::vector<int> v2(9, 2);
		v[1] = 42;
		v2 = v;
		print_container(v);
		print_container(v2);
		std::cout << v2.size() << std::endl;
	}
}
