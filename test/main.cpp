#include <iostream>
#include <array>
#include <deque>
#include "def_color.h"
#ifdef TEST
# include <vector>
# include <map>
# include <stack>
#else
# include "../vector.hpp"
# include "../stack.hpp"
# include "../map.hpp"
#endif

#define PRG_NAME "a.out"
#define COUNT 100000

#ifdef TEST
namespace ft = std;
#endif

// Global
clock_t start, end;

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
        std::cout << i->first << " => " << i->second << std::endl;
}

template <class T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

void print_header(const std::string& str, const std::string& color = COLOR_B_CYAN)
{
    std::cout << color << "\n[ " << str << " ]" COLOR_RESET << std::endl;
}

void print_time(const clock_t& start, const clock_t& end, const std::string& str = "")
{
    std::cout << std::fixed;
    std::cout << str << ": " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << std::endl;
}

void test_start(const std::string& name, const std::string& color = COLOR_B_CYAN)
{
    print_header(name, color);
#ifdef TIME
    start = clock();
#endif
}

void test_end(const std::string& name = "")
{
#ifdef TIME
    end = clock();
    print_time(start, end, name);
#else
    (void)name;
#endif
    std::cout << COLOR_RESET << std::endl;
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
    int value;
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

    /* ********************************************************************** */
    /*   vector                                                               */
    /* ********************************************************************** */

    if (has_arg == false || test_vectors[0])
    {
        print_header("vector", COLOR_B_GREEN);
        {
            const std::string name = "vector default constructor";
            test_start(name);
            ft::vector<int> v;
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            v.push_back(0);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            v.push_back(10);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            v.push_back(100);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            print_container(v);
            test_end(name);
        }
        {
            const std::string name = "size constructor";
            test_start(name);
            ft::vector<int> v(5);
            print_container(v);
            int value = 0;
            for (ft::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
                *itr = ++value;
            print_container(v);
            test_end(name);
        }
        {
            const std::string name = "size constructor error";
            test_start(name);
            try
            {
                ft::vector<int> v1;
                ft::vector<int> v2(v1.max_size() + 1);
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            test_end(name);
        }
        {
            const std::string name = "size & value constructor";
            test_start(name);
            ft::vector<int> v(10, 1) ;
            print_container(v);
            v[2] = 99 ;
            v.resize(5) ;
            print_container(v);
            v.push_back(42);
            print_container(v);

            print_header("size");
            std::cout << v.size() << std::endl;

            print_header("capacity");
            std::cout << v.capacity() << std::endl;

            leaks();
            test_end(name);
        }
        {
            const std::string name = "range constructor";
            test_start(name);
            ft::vector<int> second(4, 100);
            ft::vector<int> third(second.begin(), second.end());
            print_container(third);

            print_header("copy constructor");
            ft::vector<int> fourth(third);
            print_container(fourth);

            leaks();
            test_end(name);
        }
        {
            const std::string name = "operator= 1";
            test_start(name);
            ft::vector<int> v(10, 1);
            ft::vector<int> v2;
            v2 = v;
            v2[1] = 42;
            print_container(v);
            print_container(v2);
            test_end(name);
        }
        {
            const std::string name = "operator= 2";
            test_start(name);
            ft::vector<int> v(10, 1);
            ft::vector<int> v2(9, 2);
            v2 = v;
            v2[1] = 42;
            print_container(v);
            print_container(v2);
            std::cout << "v2.size(): " << v2.size() << std::endl;
        }
        {
            const std::string name = "operator= 3";
            test_start(name);
            ft::vector<int> v(10, 1);
            ft::vector<int> v2(20, 2);
            v2 = v;
            v2[1] = 42;
            print_container(v);
            print_container(v2);
            std::cout << "v2.size(): " << v2.size() << std::endl;
            test_end(name);
        }
        {
            const std::string name = "iterator";
            test_start(name);
            ft::vector<int> v(5);
            int value = 0;
            for (ft::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
                *itr = ++value;
            print_container(v);

            const int size = 5;
            ft::vector<foo> vct(size);
            ft::vector<foo>::iterator it(vct.begin());
            ft::vector<foo>::const_iterator ite(vct.end());
            for (int i = 0; it != ite; ++i)
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

            test_end(name);
        }
        {
            const std::string name = "reverse iterator";
            test_start(name);
            ft::vector<int> v(5);
            int value = 5;
            for (ft::vector<int>::reverse_iterator p = v.rbegin(); p != v.rend(); ++p)
                *p = value--;
            print_container(v);

            const int size = 5;
            ft::vector<foo> vct(size);
            ft::vector<foo>::reverse_iterator it(vct.rbegin());
            ft::vector<foo>::const_reverse_iterator ite(vct.rend());

            for (int i = 0; it != ite; ++i)
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

            test_end(name);
        }
        {
            const std::string name = "max_size";
            test_start(name);
            ft::vector<int> v;
            std::cout << v.max_size() << std::endl;
            test_end(name);
        }
        {
            const std::string name = "resize";
            test_start(name);
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
            test_end(name);
        }
        {
            const std::string name = "capacity, empty, reserve";
            test_start(name);
            ft::vector<int> v;
            std::cout << "capacity():\n";
            std::cout << v.capacity() << std::endl;
            std::cout << "empty():\n";
            std::cout << std::boolalpha << v.empty() << std::endl;
            v.reserve(42);
            std::cout << "v.reserve(42)\n" "capacity():\n";
            std::cout << v.capacity() << std::endl;
            test_end(name);
        }
        {
            const std::string name = "element access";
            test_start(name);
            ft::vector<int> v(10, 1);
            v[0] = 42;
            v.at(1) = 100;
            std::cout << v.at(0) << std::endl;
            std::cout << v[1] << std::endl;

            print_header("element access error", COLOR_B);
            try
            {
                v.at(100) = 42;
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            test_end(name);
        }
        {
            const std::string name = "front() & back()";
            test_start(name);
            ft::vector<int> v(5);
            int value = 0;
            for (ft::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
                *itr = ++value;
            print_container(v);
            std::cout << "front(): \n";
            std::cout << v.front() << '\n';
            std::cout << "back(): \n";
            std::cout << v.back() << std::endl;
            test_end(name);
        }
#ifndef TIME
        {
            const std::string name = "assign (sufficient capacity)";
            test_start(name);
            ft::vector<int> v(1);
            v.reserve(10);
            v.assign(3, 1);
            print_container(v);
            v.assign(2, 2);
            print_container(v);
            leaks();
            test_end(name);
        }
        {
            const std::string name = "assign (small capacity)";
            test_start(name);
            ft::vector<int> v(1);
            v.assign(3, 1);
            print_container(v);
            v.assign(10, 2);
            print_container(v);
            leaks();
            test_end(name);
        }
        {
            const std::string name = "assign (cplusplus.com example)";
            test_start(name);
            ft::vector<int> first;
            ft::vector<int> second;
            ft::vector<int> third;

            first.assign (7, 100);             // 7 ints with a value of 100

            ft::vector<int>::iterator it;
            it = first.begin() + 1;

            second.assign(it, first.end() - 1); // the 5 central values of first

            int myints[] = {1776, 7, 4};
            third.assign(myints, myints + 3);   // assigning from array.

            std::cout << "Size of first: "
                << int (first.size()) << '\n';
            std::cout << "Size of second: "
                << int (second.size()) << '\n';
            std::cout << "Size of third: "
                << int (third.size()) << '\n';
            leaks();
            test_end(name);
        }
#else
        {
            const std::string name = "assign performance testing";
            test_start(name);
            ft::vector<int> v(10, 1);
            v.reserve(COUNT + 100);
            v.assign(COUNT, 42);
            test_end(name);
        }
#endif
#ifndef TIME
        {
            const std::string name = "push_back & pop_back";
            test_start(name);
            ft::vector<int> v(1, 1);
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
            test_end(name);
        }
#else
        {
            const std::string name1 = "push_back performance testing";
            test_start(name1);
            ft::vector<int> v;
            for (int i = 0; i < COUNT; ++i)
                v.push_back(i);
            test_end(name1);

            const std::string name2 = "pop_back performance testing";
            test_start(name2);
            for (int i = 0; i < COUNT; ++i)
                v.pop_back();
            test_end(name2);
        }
#endif
#ifndef TIME
        {
            const std::string name = "insert (single element)";
            test_start(name);
            ft::vector<int> v(5, 1);
            ft::vector<int>::iterator it = v.begin() + 1;
            ft::vector<int>::iterator return_it = v.insert(it, 42);
            std::cout << "return: " << *return_it << std::endl;
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            leaks();
            test_end(name);
        }
        {
            const std::string name = "insert (fill) - 1 empty vector";
            test_start(name);
            ft::vector<int> v;
            v.insert(v.begin(), 10, 42);
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
        {
            const std::string name = "insert (fill) - 2 sufficient capacity";
            test_start(name);
            ft::vector<int> v(1, 0);
            v.push_back(1);
            v.push_back(2);
            v.push_back(3);
            v.reserve(7);
            v.insert(v.begin() + 2, 2, 100);
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
        {
            const std::string name = "insert (fill) - 3 small capacity";
            test_start(name);
            ft::vector<int> v(1, 42);
            v.insert(v.begin(), 3, 100);
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
                {
            const std::string name = "insert (range) - 1 empty";
            test_start(name);
            ft::vector<int> v;
            ft::vector<int> v2(1, 0);
            v2.push_back(1);
            v2.push_back(2);
            v.insert(v.begin(), v2.begin(), v2.end());
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
        {
            const std::string name = "insert (range) - 2 sufficient capacity";
            test_start(name);
            ft::vector<int> v(1, 42);
            v.reserve(10);
            ft::vector<int> v2(1, 0);
            v2.push_back(1);
            v2.push_back(2);
            v.insert(v.begin() + 1, v2.begin(), v2.end());
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
        {
            const std::string name = "insert (range) - 3 small capacity";
            test_start(name);
            ft::vector<int> v(2, 42);
            ft::vector<int> v2(1, 0);
            v2.push_back(1);
            v2.push_back(2);
            v.insert(v.begin(), v2.begin(), v2.end());
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
                {
            const std::string name = "erase (iterator)";
            test_start(name);
            ft::vector<int> v(5);
            int value = 0;
            for (ft::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
                *itr = ++value;
            print_container(v);

            v.erase(v.begin() + 1);
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
        {
            const std::string name = "erase (iterator, iterator)";
            test_start(name);
            ft::vector<int> v(5);
            int value = 0;
            for (ft::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
                *itr = ++value;
            print_container(v);

            ft::vector<int>::iterator return_it = v.erase(v.begin() + 1, v.begin() + 3);
            std::cout << "return: " << *return_it << std::endl;
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
        {
            const std::string name = "erase (iterator, iterator) 2 same iterator";
            test_start(name);
            ft::vector<int> v(5);
            int value = 0;
            for (ft::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
                *itr = ++value;
            print_container(v);

            ft::vector<int>::iterator return_it = v.erase(v.begin(), v.begin());
            std::cout << "return: " << *return_it << std::endl;
            print_container(v);
            std::cout << "size(): " << v.size() << std::endl;
            std::cout << "capacity(): " << v.capacity() << std::endl;
            leaks();
            test_end(name);
        }
#else
        {
            const std::string name = "insert (fill) - performance testing";
            test_start(name);
            ft::vector<int> v(10, 1);
            v.insert(v.begin() + 2, COUNT, 42);
            test_end(name);

            const std::string name2 = "insert (range) performance testing";
            test_start(name2);
            ft::vector<int> v2(10, 2);
            v2.insert(v2.begin() + 2, v.begin(), v.end());
            test_end(name2);
        }
        {
            const std::string name = "insert (fill) - performance testing 2";
            test_start(name);
            ft::vector<int> v(10, 1);
            v.reserve(COUNT + 100);
            v.insert(v.begin() + 2, COUNT, 42);
            test_end(name);

            const std::string name2 = "insert (range) performance testing 2";
            test_start(name2);
            ft::vector<int> v2(10, 2);
            v2.reserve(COUNT + 100);
            v2.insert(v2.begin() + 2, v.begin(), v.end());
            test_end(name2);

            const std::string name3 = "erase performance testing";
            test_start(name3);
            v.erase(v.begin(), v.begin() + COUNT);
            test_end(name3);
        }
#endif
        {
            const std::string name = "swap";
            test_start(name);
            ft::vector<int> foo(3, 100);   // three ints with a value of 100
            ft::vector<int> bar(5, 200);   // five ints with a value of 200
            ft::vector<int>::iterator foo_itr = foo.begin();
            ft::vector<int>::iterator bar_itr = bar.begin();

            foo.swap(bar);

            std::cout << "foo contains:\n";
            print_container(foo);
            std::cout << "foo capa: " << foo.capacity() << std::endl;
            std::cout << "foo_itr:\n";
            for (; foo_itr != bar.end(); ++foo_itr)
                std::cout << *foo_itr << '\n';

            std::cout << "bar contains:\n";
            print_container(bar);
            std::cout << "bar capa: " << bar.capacity() << std::endl;
            std::cout << "bar_itr:\n";
            for (; bar_itr != foo.end(); ++bar_itr)
                std::cout << *bar_itr << '\n';
            test_end(name);
        }
        {
            const std::string name = "get_allocator";
            test_start(name);
            ft::vector<int> myvector;
            int* p;
            unsigned int i;

            // allocate an array with space for 5 elements using vector's allocator:
            p = myvector.get_allocator().allocate(5);

            // construct values in-place on the array:
            for (i = 0; i < 5; i++)
                myvector.get_allocator().construct(&p[i], i);

            std::cout << "The allocated array contains:";
            for (i = 0; i < 5; i++)
                std::cout << ' ' << p[i];
            std::cout << '\n';

            // destroy and deallocate:
            for (i = 0; i < 5; i++)
                myvector.get_allocator().destroy(&p[i]);
            myvector.get_allocator().deallocate(p, 5);

            leaks();
            test_end(name);
        }
        {
            const std::string name = "relational operators";
            test_start(name);
            ft::vector<int> foo(3, 100);   // three ints with a value of 100
            ft::vector<int> bar(2, 200);   // two ints with a value of 200

            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo <  bar) std::cout << "foo is less than bar\n";
            if (foo >  bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
            test_end(name);
        }
        print_header("leaks");
        leaks();
    }

    /* ********************************************************************** */
    /*   map                                                                  */
    /* ********************************************************************** */

    if (has_arg == false || test_vectors[1])
    {
        print_header("map", COLOR_B_GREEN);
        {
            const std::string name = "map constructor";
            test_start(name);
            ft::map<char, int> first;   // empty
            first['a'] = 10;
            first['b'] = 30;
            first['c'] = 50;
            first['d'] = 70;

            ft::map<char, int> second(first.begin(), first.end());   // range
            ft::map<char, int> third(first);    // copy
            std::cout << "first:\n";
            print_map(first);
            std::cout << "second:\n";
            print_map(second);
            std::cout << "third:\n";
            print_map(third);
            test_end(name);
        }
        {
            const std::string name = "map constructor 2 (std::greater)";
            test_start(name);
            ft::map<char, int, std::greater<char> > first;  // empty
            first['a'] = 10;
            first['b'] = 30;
            first['c'] = 50;
            first['d'] = 70;

            ft::map<char, int, std::greater<char> > second(first.begin(),first.end());  // range
            ft::map<char, int, std::greater<char> > third(first);   // copy
            std::cout << "first:\n";
            print_map(first);
            std::cout << "second:\n";
            print_map(second);
            std::cout << "third:\n";
            print_map(third);
            test_end(name);
        }
        {
            const std::string name = "operator=, size";
            test_start(name);
            ft::map<char, int> first;
            ft::map<char, int> second;

            first['x'] = 8;
            first['y'] = 16;
            first['z'] = 32;

            second = first;                // second now contains 3 ints
            first = ft::map<char, int>();  // and first is now empty

            std::cout << "Size of first: " << first.size() << '\n';
            std::cout << "Size of second: " << second.size() << '\n';
            test_end(name);
        }
        {
            const std::string name = "iterator";
            test_start(name);
            ft::map<float, foo> mp;
            for (ft::map<float, int>::size_type i = 0; i < 10; i++)
                mp[i + 0.5] = i;

            ft::map<float, foo>::iterator it(mp.begin());
            ft::map<float, foo>::const_iterator ite(mp.begin());
            std::cout << "size: " << mp.size() << std::endl;
            std::cout << "max_size: " << mp.max_size() << std::endl;

            printPair(it);
            printPair(ite);
            std::cout << "-------" << std::endl;
            printPair(++ite);
            printPair(ite++);
            printPair(ite++);
            printPair(++ite);

            it->second.m();
            ite->second.m();

            printPair(++it);
            printPair(it++);
            printPair(it++);
            printPair(++it);
            std::cout << "-------" << std::endl;
            printPair(--ite);
            printPair(ite--);
            printPair(--ite);
            printPair(ite--);

            (*it).second.m();
            (*ite).second.m();

            printPair(--it);
            printPair(it--);
            printPair(it--);
            printPair(--it);

            test_end(name);
        }
        {
            const std::string name = "reverse_iterator";
            test_start(name);
            ft::map<char, foo> mp;
            for (ft::map<char, int>::size_type i = 0; i < 10; i++)
                mp[i + 'A'] = i;
            ft::map<char, foo>::reverse_iterator it(mp.rbegin());
            ft::map<char, foo>::const_reverse_iterator ite(mp.rbegin());
            std::cout << "size: " << mp.size() << std::endl;
            std::cout << "max_size: " << mp.max_size() << std::endl;

            printPair(it);
            printPair(ite);
            std::cout << "-------" << std::endl;
            printPair(++ite);
            printPair(ite++);
            printPair(ite++);
            printPair(++ite);

            it->second.m();
            ite->second.m();

            printPair(++it);
            printPair(it++);
            printPair(it++);
            printPair(++it);
            std::cout << "-------" << std::endl;
            printPair(--ite);
            printPair(ite--);
            printPair(--ite);
            printPair(ite--);

            (*it).second.m();
            (*ite).second.m();

            printPair(--it);
            printPair(it--);
            printPair(it--);
            printPair(--it);

            test_end(name);
        }
        {
            const std::string name = "empty";
            test_start(name);
            ft::map<int, int> mymap;

            std::cout << "mymap is ";
            if (mymap.empty() == true)
                std::cout << "empty" << std::endl;
            else
                std::cout << "not empty" << std::endl;

            mymap[0] = 0;
            std::cout << "mymap[0] = 0;\nmymap is ";
            if (mymap.empty() == true)
                std::cout << "empty" << std::endl;
            else
                std::cout << "not empty" << std::endl;
            test_end(name);
        }
        {
            const std::string name = "max_size";
            test_start(name);
            ft::map<int, int> mymap;
            std::cout << "max_size: " << mymap.max_size() << std::endl;
            test_end(name);
        }
        {
            const std::string name = "operator[]";
            test_start(name);
            ft::map<int, std::string> mymap;
            mymap[42] = "forty-two";
            mymap[100] = "hello";
            mymap[200] = "world";
            mymap[200] = "hoge";
            mymap[300] = mymap[42];
            mymap[400] = mymap[400];
            for (ft::map<int, std::string>::iterator i = mymap.begin(); i != mymap.end(); ++i)
                std::cout << i->first << ',' << i->second << std::endl;
            test_end(name);
        }
#ifndef TIME
        {
            const std::string name = "insert";
            test_start(name);
            ft::map<char, int> mymap;

            print_header("first insert function version (single parameter)", COLOR_NORMAL);
            mymap.insert(ft::pair<char, int>('a', 100));
            mymap.insert(ft::pair<char, int>('z', 200));

            ft::pair<ft::map<char, int>::iterator, bool> ret;
            ret = mymap.insert(ft::make_pair('z', 500));
            if (ret.second == false) {
                std::cout
                    << "element 'z' already existed with a value of "
                    << ret.first->second
                    << '\n';
            }

            print_header("second insert function version (with hint position)", COLOR_NORMAL);
            ft::map<char, int>::iterator it = mymap.begin();
            mymap.insert(it, ft::pair<char, int>('b', 300));
            mymap.insert(it, ft::pair<char, int>('c', 400));

            print_header("third insert function version (range insertion)", COLOR_NORMAL);
            ft::map<char, int> anothermap;
            anothermap.insert(mymap.begin(), mymap.find('c'));

            /*
            mymap contains:
            a => 100
            b => 300
            c => 400
            z => 200
            anothermap contains:
            a => 100
            b => 300
            */
            std::cout << "mymap contains:\n";
            print_map(mymap);
            std::cout << "mymap.size(): " << mymap.size() << std::endl;

            std::cout << "anothermap contains:\n";
            print_map(anothermap);
            std::cout << "anothermap.size(): " << anothermap.size() << std::endl;

            leaks();
            test_end(name);
        }
        {
            const std::string name = "erase";
            test_start(name);
            ft::map<char, int> mymap;
            ft::map<char, int>::iterator itr;
            mymap['a'] = 1;
            mymap['b'] = 2;
            mymap['c'] = 3;
            mymap['d'] = 4;
            mymap['e'] = 5;
            mymap['f'] = 6;
            print_map(mymap);

            print_header("erase(find('b')) (erasing by iterator)", COLOR_NORMAL);
            itr = mymap.find('b');
            mymap.erase(itr);
            print_map(mymap);

            print_header("erase('c') (erasing by key)", COLOR_NORMAL);
            mymap.erase('c');
            print_map(mymap);

            print_header("erase(find('e')-end()) (erasing by range)", COLOR_NORMAL);
            itr = mymap.find('e');
            mymap.erase(itr, mymap.end());
            print_map(mymap);

            std::cout << "mymap.size(): " << mymap.size() << std::endl;

            leaks();
            test_end(name);
        }
#else
        {
            const std::string name = "insert (single element) - performance testing";
            test_start(name);
            ft::map<int, int> m;
            for (int i = 0; i < COUNT; ++i)
                m.insert(ft::pair<int, int>(i, i));
            test_end(name);
        }
        {
            const std::string name = "insert (with hint) - performance testing";
            test_start(name);
            ft::map<int, int> m;
            m[COUNT] = COUNT;
            ft::map<int, int>::iterator itr = m.begin();
            for (int i = COUNT - 1; i >= 0; --i)
                m.insert(itr, ft::pair<int, int>(i, i));
            test_end(name);

            const std::string name2 = "insert (range) - performance testing";
            test_start(name2);
            ft::map<int, int> m2;
            m2.insert(m.begin(), m.end());
            test_end(name2);

            ft::map<int, int> m3(m2);

            const std::string name3 = "erase (by iterator) - performance testing";
            test_start(name3);
            for (int i = 0; i < COUNT; ++i)
                m.erase(m.begin());
            test_end(name3);

            const std::string name4 = "erase (by key) - performance testing";
            test_start(name4);
            for (int i = 0; i < COUNT; ++i)
                m2.erase(i);
            test_end(name4);

            const std::string name5 = "erase (by range) - performance testing";
            test_start(name5);
            m3.erase(m3.begin(), m3.end());
            test_end(name5);
        }
#endif
        {
            const std::string name = "swap";
            test_start(name);
            ft::map<char, int> foo, bar;
            foo['x'] = 100;
            foo['y'] = 200;

            bar['a'] = 11;
            bar['b'] = 22;
            bar['c'] = 33;

            ft::map<char, int>::iterator foo_it = foo.begin();
            ft::map<char, int>::iterator bar_it = bar.begin();
            ft::map<char, int>* foo_ptr = &foo;
            ft::map<char, int>* bar_ptr = &bar;
            ft::map<char, int>& foo_ref = foo;
            ft::map<char, int>& bar_ref = bar;

            foo.swap(bar);

            print_header("foo", COLOR_NORMAL);
            print_map(foo);
            print_header("bar", COLOR_NORMAL);
            print_map(bar);
            print_header("foo_itr", COLOR_NORMAL);
            std::cout << foo_it->first << " => " << foo_it->second << std::endl;
            print_header("bar_itr", COLOR_NORMAL);
            std::cout << bar_it->first << " => " << bar_it->second << std::endl;
            print_header("foo_ptr", COLOR_NORMAL);
            std::cout << "[a]: " << (*foo_ptr)['a'] << std::endl;
            std::cout << "[x]: " << (*foo_ptr)['x'] << std::endl;
            print_header("bar_ptr", COLOR_NORMAL);
            std::cout << "[a]: " << (*bar_ptr)['a'] << std::endl;
            std::cout << "[x]: " << (*bar_ptr)['x'] << std::endl;
            print_header("foo_ref", COLOR_NORMAL);
            std::cout << "[a]: " << foo_ref['a'] << std::endl;
            std::cout << "[x]: " << foo_ref['x'] << std::endl;
            print_header("bar_ref", COLOR_NORMAL);
            std::cout << "[a]: " << bar_ref['a'] << std::endl;
            std::cout << "[x]: " << bar_ref['x'] << std::endl;

            test_end(name);
        }
        {
            const std::string name = "clear";
            test_start(name);
            ft::map<int, int> mymap;
            for (size_t i = 0; i < 100; i++)
                mymap[i] = i;
            print_map(mymap);

            mymap.clear();
            std::cout << "clear(); size=" << mymap.size() << std::endl;
            mymap[1000] = 1101;
            mymap[2000] = 2202;
            print_map(mymap);
            test_end(name);
        }
        {
            const std::string name = "key_comp";
            test_start(name);
            ft::map<char, int> mymap;
            ft::map<char, int>::key_compare mycomp = mymap.key_comp();

            mymap['a'] = 100;
            mymap['b'] = 200;
            mymap['c'] = 300;

            std::cout << "mymap contains:\n";

            char highest = mymap.rbegin()->first;   // key value of last element

            ft::map<char, int>::iterator it = mymap.begin();
            do {
                std::cout << it->first << " => " << it->second << '\n';
            } while ( mycomp((*it++).first, highest) );
            test_end(name);
        }
        {
            const std::string name = "value_comp";
            test_start(name);
            ft::map<char, int> mymap;

            mymap['x'] = 1001;
            mymap['y'] = 2002;
            mymap['z'] = 3003;

            std::cout << "mymap contains:\n";

            ft::pair<char, int> highest = *mymap.rbegin();  // last element

            ft::map<char, int>::iterator it = mymap.begin();
            do {
                std::cout << it->first << " => " << it->second << '\n';
            } while ( mymap.value_comp()(*it++, highest) );
            test_end(name);
        }
        {
            const std::string name = "count";
            test_start(name);
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
            test_end(name);
        }
        {
            const std::string name = "lower_bound, upper_bound";
            test_start(name);
            ft::map<char, int> mymap;
            ft::map<char, int>::iterator itlow, itup;

            mymap['a'] = 20;
            mymap['b'] = 40;
            mymap['c'] = 60;
            mymap['d'] = 80;
            mymap['e'] = 100;

            print_header("non-const", COLOR_NORMAL);
            itlow = mymap.lower_bound('b');  // itlow points to b
            itup = mymap.upper_bound('d');   // itup points to e (not d!)

            mymap.erase(itlow, itup);        // erases [itlow,itup)

            // print content:
            for (ft::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            test_end(name);
        }
        {
            const std::string name = "(const) lower_bound, upper_bound";
            test_start(name);
            ft::map<char, int> mymap;
            ft::map<char, int>::const_iterator itlow, itup;

            mymap['a'] = 20;
            mymap['b'] = 40;
            mymap['c'] = 60;
            mymap['d'] = 80;
            mymap['e'] = 100;

            print_header("const", COLOR_NORMAL);
            itlow = mymap.lower_bound('b');  // itlow points to b
            itup = mymap.upper_bound('d');   // itup points to e (not d!)

            // C++98??????erase(const_iterator, const_iterator)?????????
            // mymap.erase(itlow, itup);        // erases [itlow,itup)

            // print content:
            for (; itlow != itup; ++itlow)
                std::cout << itlow->first << " => " << itlow->second << '\n';
            test_end(name);
        }
        {
            const std::string name = "equal_range";
            test_start(name);
            ft::map<char, int> mymap;

            mymap['a'] = 10;
            mymap['b'] = 20;
            mymap['c'] = 30;

            print_header("non-const", COLOR_NORMAL);
            ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
            ret = mymap.equal_range('b');

            std::cout << "lower bound points to: ";
            std::cout << ret.first->first << " => " << ret.first->second << '\n';

            std::cout << "upper bound points to: ";
            std::cout << ret.second->first << " => " << ret.second->second << '\n';

            print_header("const", COLOR_NORMAL);
            ft::pair<ft::map<char, int>::const_iterator, ft::map<char, int>::const_iterator> ret2;
            ret2 = mymap.equal_range('b');

            std::cout << "lower bound points to: ";
            std::cout << ret2.first->first << " => " << ret2.first->second << '\n';

            std::cout << "upper bound points to: ";
            std::cout << ret2.second->first << " => " << ret2.second->second << '\n';
            test_end(name);
        }
        {
            const std::string name = "get_allocator";
            test_start(name);
            int psize;
            ft::map<char, int> mymap;
            ft::pair<const char, int>* p;

            // allocate an array of 5 elements using mymap's allocator:
            p = mymap.get_allocator().allocate(5);

            // assign some values to array
            psize = sizeof(ft::map<char, int>::value_type) * 5;

            std::cout << "The allocated array has a size of " << psize << " bytes.\n";

            mymap.get_allocator().deallocate(p, 5);
            leaks();
            test_end(name);
        }
        {
            const std::string name = "get_allocator 2";
            test_start(name);
            ft::map<int, char> m;
            ft::pair<const int, char>* p = m.get_allocator().allocate(2);

            p[0].second = 'a';
            p[1].second = 'b';

            std::cout << p[0].second << std::endl;
            std::cout << p[1].second << std::endl;

            m.get_allocator().deallocate(p, 2);
            leaks();
            test_end(name);
        }
        {
            const std::string name = "relational operators";
            test_start(name);
            ft::map<char, int> foo, bar;
            foo['a'] = 100;
            foo['b'] = 200;
            bar['a'] = 10;
            bar['z'] = 1000;

            // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo <  bar) std::cout << "foo is less than bar\n";
            if (foo >  bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
            test_end(name);
        }
        {
            const std::string name = "swap (non-member function)";
            test_start(name);
            ft::map<char, int> foo, bar;

            foo['x'] = 100;
            foo['y'] = 200;

            bar['a'] = 11;
            bar['b'] = 22;
            bar['c'] = 33;

            swap(foo, bar);

            std::cout << "foo contains:\n";
            print_map(foo);
            std::cout << "bar contains:\n";
            print_map(bar);
            test_end(name);
        }
        print_header("leaks");
        leaks();
    }

    /* ********************************************************************** */
    /*   stack                                                                */
    /* ********************************************************************** */

    if (has_arg == false || test_vectors[2])
    {
        print_header("stack", COLOR_B_GREEN);
        {
            const std::string name = "stack constructor, top, size";
            test_start(name);
            std::deque<int> mydeque(3, 100);    // three ints with value 100
            ft::stack<int, std::deque<int> > s(mydeque);
            std::cout << "s.top(): " << s.top() << std::endl;
            std::cout << "s.size(): " << s.size() << std::endl;
            test_end(name);
        }
        {
            const std::string name = "empty";
            test_start(name);
            ft::stack<int> s;
            std::cout << "s.empty(): " << s.empty() << std::endl;
            s.push(42);
            std::cout << "s.empty(): " << s.empty() << std::endl;
            std::cout << "s.top(): " << s.top() << std::endl;
            test_end(name);
        }
#ifndef TIME
        {
            const std::string name = "push, pop";
            test_start(name);
            ft::stack<int> mystack;
            for (int i = 0; i < 5; ++i)
                mystack.push(i);

            std::cout << "Popping out elements...";
            while (!mystack.empty())
            {
                std::cout << ' ' << mystack.top();
                mystack.pop();
            }
            std::cout << '\n';
            test_end(name);
        }
#else
        {
            const std::string name = "push - performance testing";
            test_start(name);
            ft::stack<int> mystack;
            for (int i = 0; i < COUNT; ++i)
                mystack.push(i);
            test_end(name);

            const std::string name2 = "pop - performance testing";
            test_start(name2);
            while (!mystack.empty())
                mystack.pop();
            test_end(name2);
        }
#endif
        {
            const std::string name = "relational operators";
            test_start(name);
            ft::stack<int> foo;
            foo.push(42);
            ft::stack<int> bar;
            bar.push(21);
            bar.push(100);

            // foo (42) vs bar (21, 100):
            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo <  bar) std::cout << "foo is less than bar\n";
            if (foo >  bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
            test_end(name);
        }
        print_header("leaks");
        leaks();
    }
}
