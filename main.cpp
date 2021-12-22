#include <iostream>
#include <array>
#include <vector>
#include "vector.hpp"

#define PRG_NAME "a.out"

/*
** Text color
*/
#define COLOR_NORMAL ""
#define COLOR_RESET	"\033[m"
#define COLOR_RED	"\033[31m"
#define COLOR_CYAN	"\033[36m"

/*
** Text bold color
*/
#define COLOR_B			"\033[1m"
#define COLOR_B_BLACK	"\033[1;30m"
#define COLOR_B_RED		"\033[1;31m"
#define COLOR_B_GREEN	"\033[1;32m"
#define COLOR_B_YELLOW	"\033[1;33m"
#define COLOR_B_BLUE	"\033[1;34m"
#define COLOR_B_MAGENTA	"\033[1;35m"
#define COLOR_B_CYAN	"\033[1;36m"
#define COLOR_B_WHITE	"\033[1;37m"

template <class T>
void print_container(T& container)
{
	std::cout << "{ ";
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		std::cout <<  *it << ' ';
	std::cout << '}' << std::endl;
}

void print_header(const std::string& str, const std::string& color = COLOR_B_CYAN)
{
	std::cout << color << "\n[ " << str << " ]" COLOR_RESET << std::endl;
}

void leaks()
{
	print_header("leaks Report", COLOR_B);
	if (system("leaks -q " PRG_NAME))
		std::cout << COLOR_RED << "LEAK!" << COLOR_RESET << std::endl;
}

int main()
{
	{
		print_header("default constructor");
		ft::vector<int> v;
		std::cout << v.size() << std::endl;
		std::cout << v.capacity() << std::endl;
		v.push_back(21);
		std::cout << v.size() << std::endl;
		std::cout << v.capacity() << std::endl;
		v.push_back(42);
		std::cout << v.size() << std::endl;
		std::cout << v.capacity() << std::endl;
		v.push_back(84);
		std::cout << v.size() << std::endl;
		std::cout << v.capacity() << std::endl;
		print_container(v);
	}
	{
		// ft::vector<int> v;
		// std::cout << v.size() << std::endl;
		print_header("size & value constructor");
		ft::vector<int> v(10, 1) ;
		v[2] = 99 ;
		v.resize(5) ;
		print_container(v);
		v.push_back(42);
		print_container(v);

		print_header("size", COLOR_B);
		std::cout << v.size() << std::endl;
		print_header("capa", COLOR_B);
		std::cout << v.capacity() << std::endl;
		leaks();
	}
	{
		print_header("iterator");
		ft::vector<int> v(5);
		int value = 0;
		for (ft::vector<int>::iterator p = v.begin(); v.end() != p; p = 1 + p)
			*p = ++value;
		print_container(v);
	}
	{
		print_header("reverse iterator");
		ft::vector<int> v(5);
		int value = 5;
		for (ft::vector<int>::reverse_iterator p = v.rbegin(); p != v.rend(); ++p)
			*p = value--;
		print_container(v);
	}
	{
		print_header("iterator constructor");
		std::array<int, 5> v = {100, 2, 3, 4, 5};
		ft::vector<int> v2(std::begin(v), std::end(v));
		print_container(v2);
		leaks();
	}
	{
		print_header("iterator constructor 2");
		std::vector<int> v(5, 10);
		ft::vector<int> v2(std::begin(v), std::end(v));
		print_container(v2);
		leaks();
	}
	{
		print_header("copy constructor");
		ft::vector<int> v(5);
		int value = 0;
		for (ft::vector<int>::iterator p = v.begin(); v.end() != p; p = 1 + p)
			*p = ++value;
		ft::vector<int> v2(v);
		v2.push_back(42);

		print_container(v);
		print_container(v2);
		leaks();
	}
	{
		print_header("assignment");
		ft::vector<int> v(10, 1);
		ft::vector<int> v2(v);
		v2[1] = 42;
		print_container(v);
		print_container(v2);
	}
	{
		print_header("assignment 2");
		ft::vector<int> v(10, 1);
		ft::vector<int> v2(9, 2);
		v[1] = 42;
		v2 = v;
		print_container(v);
		print_container(v2);
		std::cout << v2.size() << std::endl;
	}
	print_header("leaks");
	leaks();
}
