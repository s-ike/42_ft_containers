#include <vector>
#include <map>
#include <stack>
#include "../vector.hpp"
#include "../stack.hpp"
#include "../map.hpp"
#include "def_color.h"

#define COUNT 100000

void print_header(const std::string& str, const std::string& color = COLOR_B_CYAN)
{
    std::cout << color << "\n[ " << str << " ]" COLOR_RESET << std::endl;
}

void print_time(const std::string& str, const clock_t& start, const clock_t& end)
{
    std::cout << std::fixed;
    std::cout << str << (double)(end - start) / CLOCKS_PER_SEC * 1000 << std::endl;
}

int main()
{
    clock_t start, end;
    {
        print_header("vector push_back");

        start = clock();
        ft::vector<int> v1;
        for (int i = 0; i < COUNT; ++i)
            v1.push_back(i);
        end = clock();
        print_time("ft::vector:  ", start, end);

        start = clock();
        std::vector<int> v2;
        for (int i = 0; i < COUNT; ++i)
            v2.push_back(i);
        end = clock();
        print_time("std::vector: ", start, end);


        print_header("vector pop_back");

        start = clock();
        for (int i = 0; i < COUNT; ++i)
            v1.pop_back();
        end = clock();
        print_time("ft::vector:  ", start, end);

        start = clock();
        for (int i = 0; i < COUNT; ++i)
            v2.pop_back();
        end = clock();
        print_time("std::vector: ", start, end);
    }
    {
        print_header("stack push");

        start = clock();
        ft::stack<int> s1;
        for (int i = 0; i < COUNT; ++i)
            s1.push(i);
        end = clock();
        print_time("ft::stack:  ", start, end);

        start = clock();
        std::stack<int> s2;
        for (int i = 0; i < COUNT; ++i)
            s2.push(i);
        end = clock();
        print_time("std::stack: ", start, end);


        print_header("stack pop");

        start = clock();
        for (int i = 0; i < COUNT; ++i)
            s1.pop();
        end = clock();
        print_time("ft::stack:  ", start, end);

        start = clock();
        for (int i = 0; i < COUNT; ++i)
            s2.pop();
        end = clock();
        print_time("std::stack: ", start, end);
    }
    {
        print_header("map insert");

        start = clock();
        ft::map<int, int> m1;
        for (int i = 0; i < COUNT; ++i)
            m1.insert(ft::pair<int, int>(i, i));
        end = clock();
        print_time("ft::map:  ", start, end);

        start = clock();
        std::map<int, int> m2;
        for (int i = 0; i < COUNT; ++i)
            m2.insert(std::pair<int, int>(i, i));
        end = clock();
        print_time("std::map: ", start, end);


        print_header("map erase");

        start = clock();
        for (int i = 0; i < COUNT; ++i)
            m1.erase(i);
        end = clock();
        print_time("ft::map:  ", start, end);

        start = clock();
        for (int i = 0; i < COUNT; ++i)
            m2.erase(i);
        end = clock();
        print_time("std::map: ", start, end);
    }
}
