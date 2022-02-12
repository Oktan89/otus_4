#pragma once
#include <type_traits>
#include <iostream>
#include <string>
#include <vector>
#include <list>



template<typename T, typename U = typename std::enable_if_t<!std::is_same_v<std::basic_string<char>, T>, void>>
decltype(std::declval<T>().begin(), std::declval<T>().end(), void()) print_ip(const T& Conteiner)
{
    for(auto it = Conteiner.begin(); it != Conteiner.end(); ++it)
    {
        if(it != Conteiner.begin())
        {
            std::cout <<".";
        }
        std::cout << *it; 
    }
    std::cout<<std::endl;
}

template<typename T, typename U = typename std::enable_if_t<std::is_same_v<std::basic_string<char>, T>, void>>
void print_ip(const T& value)
{
    std::cout << value << std::endl;
}

template<typename T, typename U = typename std::enable_if_t<std::is_integral_v<T>>, typename = void>
void print_ip(const T& ival)
{
    std::cout <<"intergarl" << ival <<std::endl;
    char* byte = reinterpret_cast<char*>(ival);
    for(std::size_t i = 0; i < sizeof(T); ++i)
    {
        std::cout<< byte <<".";
        ++byte;
    }
    std::cout<< std::endl;
}