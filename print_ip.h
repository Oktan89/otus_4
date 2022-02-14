#pragma once
#include <type_traits>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>




template<typename T, typename = typename std::enable_if_t<!std::is_same_v<std::basic_string<char>, T>, void>>
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

template<typename T>
decltype(std::declval<T>().c_str(), void()) print_ip(const T& value)
{
    std::cout << value << std::endl;
}

template<typename T, typename = typename std::enable_if_t<std::is_integral_v<T>>>
decltype(std::declval<T>(), void()) print_ip(const T& ival)
{
    T value = std::remove_cv_t<T>(ival);
    
    unsigned char* byte = reinterpret_cast<unsigned char*>(&value);
    byte += sizeof(T)-1;
    for(std::size_t i = sizeof(T); i > 0 ; --i)
    {
        if(i != sizeof(T))
            std::cout<< ".";
        std::cout<< static_cast<int>(*byte);
        --byte;
    }
    std::cout<< std::endl;
}

template<typename T, std::size_t N>
struct printtuple
{
    static void print(const T& tuple)
    {
        printtuple<T, N-1>::print(tuple);
        std::cout << "." << std::get<N-1>(tuple);
               
    }
};

template<typename T>
struct printtuple<T, 1>
{
    static void print(const T& tuple)
    {
        std::cout << std::get<0>(tuple);
    }
};

template<typename... T>
void print_ip([[maybe_unused]] std::tuple<T...>&& args)
{  
    printtuple<decltype(args), sizeof...(T)>::print(args);
    std::cout << std::endl;
}