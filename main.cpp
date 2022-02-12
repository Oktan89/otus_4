#include <iostream>
#include <tuple>
#include "print_ip.h"


int main(int, char**)
{
    
    print_ip(std::vector<int>{100, 200, 300, 400});
    print_ip(std::list<short>{400, 300, 200, 100});
    print_ip(std::string{"Hello, World!"});
    print_ip(int8_t{-1});
    
    // print_ip(std::make_tuple(123, 456, 789, 0) );

    
    return 0;
}