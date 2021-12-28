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

#ifdef TEST
#define ft std
#endif

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
#ifndef NO_LEAKS
	print_header("leaks Report", COLOR_B);
	if (system("leaks -q " PRG_NAME))
		std::cout << COLOR_RED << "LEAK!" << COLOR_RESET << std::endl;
#endif
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
		print_header("size constructor");
		std::vector<int> v(5);
		int value = 0;
		for (std::vector<int>::iterator p = v.begin(); v.end() != p; p = 1 + p)
			*p = ++value;
		print_container(v);
	}
	{
		print_header("size constructor error");
		try
		{
			ft::vector<int> v(4611686018427387904);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
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
		print_header("max_size", COLOR_B);
		std::cout << v.max_size() << std::endl;
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
	{
		print_header("resize");
		ft::vector<int> v(10, 1);
		print_container(v);
		std::cout << "v.resize(5): " << std::endl;
		v.resize(5);
		print_container(v);
		std::cout << "v.resize(8, 100): " << std::endl;
		v.resize(8, 100);
		print_container(v);
		std::cout << "v.resize(12): " << std::endl;
		v.resize(12);
		print_container(v);
		leaks();
	}
	{
		print_header("Element access");
		ft::vector<int> v(10, 1);
		v[0] = 42;
		v.at(1) = 100;
		print_container(v);

		print_header("element access error", COLOR_B);
		try
		{
			v.at(100) = 42;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	{
		print_header("front() & back()");
		ft::vector<int> v(5);
		int value = 0;
		for (ft::vector<int>::iterator p = v.begin(); v.end() != p; p = 1 + p)
			*p = ++value;
		print_container(v);
		std::cout << "front(): \n";
		std::cout << v.front() << '\n';
		std::cout << "back(): \n";
		std::cout << v.back() << std::endl;
	}
	{
		print_header("assign (sufficient capacity)");
		ft::vector<int> v(1);
		v.reserve(10);
		v.assign(3, 1);
		print_container(v);
		v.assign(2, 2);
		print_container(v);
		leaks();
	}
	{
		print_header("assign (small capacity)");
		ft::vector<int> v(1);
		v.assign(3, 1);
		print_container(v);
		v.assign(10, 2);
		print_container(v);
		leaks();
	}
	{
		print_header("assign (cplusplus.com)");
		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int> third;

		first.assign (7,100);             // 7 ints with a value of 100

		ft::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.

		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
		std::cout << "Size of third: " << int (third.size()) << '\n';
		leaks();
	}
	{
		print_header("push_back() & pop_back()");
		std::vector<int> v(1, 1);
		v.push_back(2);
		/*
		[ STL ]
		size():
		2
		capacity():
		2
		*/
		std::cout << "size(): \n" << v.size() << std::endl;
		std::cout << "capacity(): \n" << v.capacity() << std::endl;
		v.push_back(3);
		/*
		[ STL ]
		size():
		3
		capacity():
		4
		*/
		std::cout << "size(): \n" << v.size() << std::endl;
		std::cout << "capacity(): \n" << v.capacity() << std::endl;

		print_container(v);

		v.pop_back();
		/*
		[ STL ]
		size():
		2
		capacity():
		4
		*/
		std::cout << "size(): \n" << v.size() << std::endl;
		std::cout << "capacity(): \n" << v.capacity() << std::endl;

		print_container(v);
	}
	{
		print_header("insert(iterator, const value_type&)");
		ft::vector<int> v(5, 1);
		/* { 42 5 }
		std::vector<int>::iterator it = v.begin();
		v.insert(it, 42);
		*/
		ft::vector<int>::iterator it = v.begin() + 1;
		ft::vector<int>::iterator return_it = v.insert(it, 42);
		print_header("return", COLOR_B);
		std::cout << *return_it << std::endl;
		print_container(v);
		print_header("size()", COLOR_B);
		std::cout << v.size() << std::endl;
		// print_header("capacity()", COLOR_B);
		// std::cout << v.capacity() << std::endl;
		leaks();
	}
	{
		print_header("insert(iterator, size_type, value_type&)");
		ft::vector<int> v(2, 1);
		v.insert(v.begin() + 1, 4, 42);
		print_container(v);
		print_header("size()", COLOR_B);
		std::cout << v.size() << std::endl;
		// print_header("capacity()", COLOR_B);
		// std::cout << v.capacity() << std::endl;
		leaks();
	}
	{
		print_header("insert(iterator, InputIterator, InputIterator) 1");
		ft::vector<int> v(2, 1);
		ft::vector<int> v2(1, 42);
		v2.push_back(100);
		v2.push_back(200);
		v.insert(v.begin() + 1, v2.begin(), v2.end());
		print_container(v);
	}
	{
		print_header("insert(iterator, InputIterator, InputIterator) 2");
		ft::vector<int> v;
		ft::vector<int> v2(1, 42);
		v2.push_back(100);
		v2.push_back(200);
		v.insert(v.begin(), v2.begin(), v2.end());
		print_container(v);
	}
	{
		print_header("erase(iterator)");
		ft::vector<int> v(5);
		int value = 0;
		for (ft::vector<int>::iterator p = v.begin(); v.end() != p; p = 1 + p)
			*p = ++value;
		print_container(v);
		v.erase(v.begin() + 1);
		print_container(v);
	}
	{
		print_header("erase(iterator, iterator)");
		ft::vector<int> v(5);
		int value = 0;
		for (ft::vector<int>::iterator p = v.begin(); v.end() != p; p = 1 + p)
			*p = ++value;
		print_container(v);
		ft::vector<int>::iterator return_it = v.erase(v.begin() + 1, v.begin() + 3);
		print_header("return", COLOR_B);
		std::cout << *return_it << std::endl;
		print_container(v);
	}
	{
		print_header("swap");
		ft::vector<int> foo(3,100);   // three ints with a value of 100
		ft::vector<int> bar(5,200);   // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:\n";
		print_container(foo);
		std::cout << "foo capa: " << foo.capacity() << std::endl;

		std::cout << "bar contains:\n";
		print_container(bar);
		std::cout << "bar capa: " << bar.capacity() << std::endl;
	}
	{
		print_header("get_allocator");
		ft::vector<int> myvector;
		int * p;
		unsigned int i;

		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);

		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);

		leaks();
	}
	{
		print_header("relational operators");
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	print_header("leaks");
	leaks();
}
