#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <stack>
#include <deque>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

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

template <class T>
void print_map(T& mymap)
{
	for (typename T::iterator i = mymap.begin(); i != mymap.end(); ++i)
		std::cout << i->first << ',' << i->second << std::endl;
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

class foo
{
public:
	foo(void) { };
	~foo(void) { };
	void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
	void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
	foo &operator=(int src) { this->value = src; return *this; };
	int getValue(void) const { return this->value; };
private:
	int	value;
};
std::ostream &operator<<(std::ostream &o, foo const &bar)
{
	o << bar.getValue();
	return o;
}

int main(int argc, char **argv)
{
	bool has_arg = false;
	// [0]:vector, [1]:map, [2]:stack
	bool test_vectors[] = {false, false, false};
	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{
			std::string arg = argv[i];
			if (arg == "vector")
			{
				has_arg = true;
				test_vectors[0] = true;
			}
			else if (arg == "map")
			{
				has_arg = true;
				test_vectors[1] = true;
			}
			else if (arg == "stack")
			{
				has_arg = true;
				test_vectors[2] = true;
			}
		}

	}
	if (has_arg == false || test_vectors[0])
	{
		print_header("vector", COLOR_B_GREEN);
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

			const int size = 5;
			ft::vector<foo> vct(size);
			ft::vector<foo>::iterator it(vct.begin());
			ft::vector<foo>::const_iterator ite(vct.end());
			for (int i = 1; it != ite; ++i)
			*it++ = i;
			std::cout << "vct.size(): " << vct.size() << std::endl;

			it = vct.begin();
			ite = vct.begin();

			std::cout << *(++ite) << std::endl;
			std::cout << *(ite++) << std::endl;
			std::cout << *ite++ << std::endl;
			std::cout << *++ite << std::endl;

			it->m();
			ite->m();

			std::cout << *(++it) << std::endl;
			std::cout << *(it++) << std::endl;
			std::cout << *it++ << std::endl;
			std::cout << *++it << std::endl;
			std::cout << "-------" << std::endl;
			std::cout << *(--ite) << std::endl;
			std::cout << *(ite--) << std::endl;
			std::cout << *--ite << std::endl;
			std::cout << *ite-- << std::endl;

			(*it).m();
			(*ite).m();

			std::cout << *(--it) << std::endl;
			std::cout << *(it--) << std::endl;
			std::cout << *it-- << std::endl;
			std::cout << *--it << std::endl;
		}
		{
			print_header("reverse iterator");
			ft::vector<int> v(5);
			int value = 5;
			for (ft::vector<int>::reverse_iterator p = v.rbegin(); p != v.rend(); ++p)
				*p = value--;
			print_container(v);

			const int size = 5;
			ft::vector<foo> vct(size);
			ft::vector<foo>::reverse_iterator it(vct.rbegin());
			ft::vector<foo>::const_reverse_iterator ite(vct.rend());

			for (int i = 1; it != ite; ++i)
				*it++ = (i * 7);
			std::cout << "vct.size(): " << vct.size() << std::endl;

			it = vct.rbegin();
			ite = vct.rbegin();

			std::cout << *(++ite) << std::endl;
			std::cout << *(ite++) << std::endl;
			std::cout << *ite++ << std::endl;
			std::cout << *++ite << std::endl;

			it->m();
			ite->m();

			std::cout << *(++it) << std::endl;
			std::cout << *(it++) << std::endl;
			std::cout << *it++ << std::endl;
			std::cout << *++it << std::endl;
			std::cout << "-------" << std::endl;
			std::cout << *(--ite) << std::endl;
			std::cout << *(ite--) << std::endl;
			std::cout << *--ite << std::endl;
			std::cout << *ite-- << std::endl;

			(*it).m();
			(*ite).m();

			std::cout << *(--it) << std::endl;
			std::cout << *(it--) << std::endl;
			std::cout << *it-- << std::endl;
			std::cout << *--it << std::endl;
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
			std::cout << "v2.size(): " << v2.size() << std::endl;
		}
		{
			print_header("assignment 3");
			ft::vector<int> v(10, 1);
			ft::vector<int> v2;
			v[1] = 42;
			v2 = v;
			print_container(v);
			print_container(v2);
			std::cout << "v2.size(): " << v2.size() << std::endl;
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
			print_header("capacity, empty, reserve");
			ft::vector<int> v;
			std::cout << "capacity():\n";
			std::cout << v.capacity() << std::endl;
			std::cout << "empty():\n";
			std::cout << std::boolalpha << v.empty() << std::endl;
			v.reserve(42);
			std::cout << "v.reserve(42)\n" "capacity():\n";
			std::cout << v.capacity() << std::endl;
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
			ft::vector<int>::iterator it = v.begin() + 1;
			ft::vector<int>::iterator return_it = v.insert(it, 42);
			print_header("return", COLOR_B);
			std::cout << *return_it << std::endl;
			print_container(v);
			print_header("size()", COLOR_B);
			std::cout << v.size() << std::endl;
			leaks();
		}
		{
			print_header("insert(iterator, size_type, value_type&)");
			ft::vector<int> v(2, 1);
			v.insert(v.begin() + 1, 4, 42);
			print_container(v);
			print_header("size()", COLOR_B);
			std::cout << v.size() << std::endl;
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
	// map
	if (has_arg == false || test_vectors[1])
	{
		print_header("map", COLOR_B_GREEN);
		{
			ft::map<char, int> mymap;
			std::cout << mymap.size() << std::endl;
		}
		{
			print_header("ft");
			ft::map<int, int> mymap;
			ft::pair<int, int> data = ft::make_pair(42, 42);
			std::cout << "[ insert(1) 1 ]" << std::endl;
			ft::pair<ft::map<int, int>::iterator, bool> re = mymap.insert(data);
			ft::map<int, int>::iterator itr = re.first;
			std::cout << "re.first: " << (*itr).first << std::endl;
			std::cout << "re.second: " << re.second << std::endl;
			std::cout << "[ insert(1) 2 ]" << std::endl;
			re = mymap.insert(ft::make_pair(100, 100));
			itr = re.first;
			std::cout << "re.first: " << (*itr).first << std::endl;
			std::cout << "re.second: " << re.second << std::endl;

			std::cout << "[ insert(2) ]" << std::endl;
			ft::map<int, int>::iterator itr2 = mymap.insert(itr, ft::make_pair(200, 200));
			std::cout << (*itr2).first << std::endl;

			for (ft::map<int, int>::iterator i = mymap.begin(); i != mymap.end(); ++i)
				std::cout << (*i).first << ',' << (*i).second << std::endl;

			print_header("range constructor");
			ft::map<int, int> newmap(mymap.begin(), mymap.end());
			for (ft::map<int, int>::iterator i = newmap.begin(); i != newmap.end(); ++i)
				std::cout << (*i).first << ',' << (*i).second << std::endl;

			print_header("copy constructor");
			ft::map<int, int> copymap(mymap);
			for (ft::map<int, int>::iterator i = copymap.begin(); i != copymap.end(); ++i)
				std::cout << (*i).first << ',' << (*i).second << std::endl;

			print_header("assignment");
			std::cout << "mymap.insert(1, 1)\n";
			mymap.insert(ft::make_pair(1, 1));
			std::cout << "copymap = mymap\n";
			copymap = mymap;
			for (ft::map<int, int>::iterator i = copymap.begin(); i != copymap.end(); ++i)
				std::cout << (*i).first << ',' << (*i).second << std::endl;
		}
		{
			print_header("insert 3");
			ft::map<char, int> mymap;
			ft::pair<ft::map<char, int>::iterator, bool> re = mymap.insert(ft::make_pair('a', 1));
			mymap.insert(ft::make_pair('b', 2));
			re = mymap.insert(ft::make_pair('c', 3));
			mymap.insert(ft::make_pair('d', 4));

			ft::map<char, int> anothermap;
			anothermap.insert(mymap.begin(), re.first);
			for (ft::map<char, int>::iterator i = anothermap.begin(); i != anothermap.end(); ++i)
				std::cout << (*i).first << ',' << (*i).second << std::endl;

			print_header("reverse_iterator");
			for (ft::map<char, int>::reverse_iterator i = anothermap.rbegin(); i != anothermap.rend(); ++i)
				std::cout << (*i).first << ',' << (*i).second << std::endl;
		}
		{
			print_header("ft 2");
			ft::map<int, int> mymap;
			ft::pair<int, int> data = ft::make_pair(42, 42);
			std::cout << "[ insert(1) 1 ]" << std::endl;
			ft::pair<ft::map<int, int>::iterator, bool> re = mymap.insert(data);
			ft::map<int, int>::iterator itr = re.first;
			std::cout << "[ insert(1) 2 ]" << std::endl;
			mymap.insert(ft::make_pair(100, 100));
			// itr = re.first;
			std::cout << "[ iterator ]" << std::endl;
			std::cout << (*itr).first << std::endl;
			++itr;
			std::cout << (*itr).first << std::endl;
			// 範囲外
			// ++itr;
			// std::cout << (*itr).first << std::endl;

			// 最大値のイテレータを++
			std::cout << "[ iterator 2 ]" << std::endl;
			re = mymap.insert(ft::make_pair(200, 200));
			itr = re.first;
			std::cout << (*itr).first << std::endl;
			// 範囲外
			// ++itr;
			// std::cout << (*itr).first << std::endl;

			// 最小値のイテレータを--
			std::cout << "[ iterator 3 ]" << std::endl;
			re = mymap.insert(ft::make_pair(1, 1));
			itr = re.first;
			std::cout << (*itr).first << std::endl;
			// 範囲外（segmentation fault）
			// --itr;
			// std::cout << (*itr).first << std::endl;
		}
		{
			print_header("max_size");
			std::map<int, int> mymap;
			std::cout << "max_size: " << mymap.max_size() << std::endl;
		}
		{
			print_header("operator[]");
			ft::map<int, std::string> mymap;
			mymap[42] = "42";
			mymap[100] = "hello";
			mymap[200] = "world";
			mymap[200] = "hoge";
			mymap[300] = mymap[42];
			mymap[400] = mymap[400];
			for (ft::map<int, std::string>::iterator i = mymap.begin(); i != mymap.end(); ++i)
				std::cout << i->first << ',' << i->second << std::endl;
		}
		{
			print_header("erase");
			ft::map<char, int> mymap;
			ft::map<char, int>::iterator itr;
			mymap['a'] = 1;
			mymap['b'] = 2;
			mymap['c'] = 3;
			mymap['d'] = 4;
			mymap['e'] = 5;
			mymap['f'] = 6;
			print_map(mymap);
			std::cout << "erase(find('b')) (erasing by iterator)" << std::endl;
			itr = mymap.find('b');
			mymap.erase(itr);
			print_map(mymap);
			std::cout << "erase('c') (erasing by key)" << std::endl;
			mymap.erase('c');
			print_map(mymap);
			std::cout << "erase(find('e')-end()) (erasing by range)" << std::endl;
			itr = mymap.find('e');
			mymap.erase(itr, mymap.end());
			print_map(mymap);
			leaks();
		}
		{
			print_header("swap");
			ft::map<char, int> foo, bar;
			foo['x'] = 100;
			foo['y'] = 200;

			bar['a'] = 11;
			bar['b'] = 22;
			bar['c'] = 33;

			foo.swap(bar);

			print_header("foo", COLOR_NORMAL);
			print_map(foo);
			print_header("bar", COLOR_NORMAL);
			print_map(bar);
		}
		{
			print_header("clear");
			ft::map<int, int> mymap;

			for (size_t i = 0; i < 100; i++)
				mymap[i] = i;
			print_map(mymap);

			mymap.clear();
			std::cout << "clear(); size=" << mymap.size() << std::endl;
			mymap[1000] = 1101;
			mymap[2000] = 2202;
			print_map(mymap);
		}
		{
			print_header("key_comp");
			ft::map<char, int> mymap;

			ft::map<char, int>::key_compare mycomp = mymap.key_comp();

			mymap['a'] = 100;
			mymap['b'] = 200;
			mymap['c'] = 300;

			std::cout << "mymap contains:\n";

			char highest = mymap.rbegin()->first;     // key value of last element

			ft::map<char, int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
			} while ( mycomp((*it++).first, highest) );
		}
		{
			print_header("value_comp");
			ft::map<char, int> mymap;

			mymap['x'] = 1001;
			mymap['y'] = 2002;
			mymap['z'] = 3003;

			std::cout << "mymap contains:\n";

			ft::pair<char, int> highest = *mymap.rbegin();          // last element

			ft::map<char, int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
			} while ( mymap.value_comp()(*it++, highest) );
		}
		{
			print_header("swap (non-member)");
			ft::map<char, int> foo, bar;
			foo['x'] = 100;
			foo['y'] = 200;

			bar['a'] = 11;
			bar['b'] = 22;
			bar['c'] = 33;

			swap(foo,bar);

			print_header("foo", COLOR_NORMAL);
			print_map(foo);
			print_header("bar", COLOR_NORMAL);
			print_map(bar);
		}
		{
			print_header("count");
			ft::map<char, int> mymap;
			char c;

			mymap['a'] = 101;
			mymap['c'] = 202;
			mymap['f'] = 303;

			for (c = 'a'; c < 'h'; c++)
			{
				std::cout << c;
				if (mymap.count(c) > 0)
					std::cout << " is an element of mymap.\n";
				else
					std::cout << " is not an element of mymap.\n";
			}
		}
		{
			print_header("lower_bound, upper_bound");
			ft::map<char, int> mymap;
			ft::map<char, int>::iterator itlow, itup;

			mymap['a'] = 20;
			mymap['b'] = 40;
			mymap['c'] = 60;
			mymap['d'] = 80;
			mymap['e'] = 100;

			itlow = mymap.lower_bound('b');  // itlow points to b
			itup = mymap.upper_bound('d');   // itup points to e (not d!)

			mymap.erase(itlow,itup);        // erases [itlow,itup)

			// print content:
			for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		print_header("leaks");
		leaks();
	}
	// stack
	if (has_arg == false || test_vectors[2])
	{
		print_header("stack", COLOR_B_GREEN);
		{
			print_header("constructor, top, size");
			std::deque<int> mydeque(3,100);
			ft::stack<int, std::deque<int> > s(mydeque);
			std::cout << "s.top(): " << s.top() << std::endl;
			std::cout << "s.size(): " << s.size() << std::endl;
		}
		{
			print_header("empty");
			ft::stack<int> s;
			std::cout << s.empty() << std::endl;
			s.push(42);
			std::cout << s.empty() << std::endl;
			std::cout << s.top() << std::endl;
		}
		{
			print_header("push, pop");
			ft::stack<int> mystack;

			for (int i=0; i<5; ++i) mystack.push(i);

			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
				std::cout << ' ' << mystack.top();
				mystack.pop();
			}
			std::cout << '\n';
		}
		{
			print_header("relational operators");
			ft::stack<int> foo;
			foo.push(42);
			ft::stack<int> bar;
			bar.push(21);
			bar.push(100);

			if (foo==bar) std::cout << "foo and bar are equal\n";
			if (foo!=bar) std::cout << "foo and bar are not equal\n";
			if (foo< bar) std::cout << "foo is less than bar\n";
			if (foo> bar) std::cout << "foo is greater than bar\n";
			if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		}
	}
}
