/**
 * @file print_ip.h
 * @author Ruslan Zhigalenko (r.zhigalenko@mail.ru)
 * @brief Заголовочный файл с определением перегрузок шаблонной функции
 * @version 0.1
 * @date 2022-02-16
 * 
 * @copyright Copyright (c) 2022
 * 
Файл содержит функцию печати условного IP-адреса.
Условность его заключается в том, что количество элементов не обязательно должно быть равно 4-
ём или 8-ми, а также каждый элемент не обязательно должен быть числом из диапазона 0..255. От
идеи IP-адреса остаётся фактически только вывод элементов через `.` (символ точки).

 *@warning Функция реализована через механизм SFINAE
 */
#pragma once
#include <type_traits>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>


/**
 * @brief Реализация печати целочисленного типа
 * @ingroup print_ip
 * 
 * Адрес может быть представлен в виде произвольного целочисленного типа. Выводить
 * побайтово в беззнаковом виде, начиная со старшего байта, с символом `.` (символ точки)
 * 
 * @param ival интегральный тип
 */
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

/**
 * @brief Реализация печати контейнеров
 * @ingroup print_ip
 * 
 * Адрес может быть представлен в виде контейнеров `std::list`, `std::vector`.
 * Выводится полное содержимое контейнера поэлементно и разделяется `.` (символом
 * точка). Элементы выводятся как есть.
 * 
 * @param Conteiner Любой контейнер
 */
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

/**
 * @brief Реализация печати std::string
 * @ingroup print_ip
 * 
 * Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от
 *содержимого.

 * @param value std::string
 */
template<typename T>
decltype(std::declval<T>().c_str(), void()) print_ip(const T& value)
{
    std::cout << value << std::endl;
}

/**
 * @brief Шаг рекурсии вывода элементов кортежа с проверкой в compile time
 * 
 * @tparam T Тип кортежа
 * @tparam N Индекс кортежа
 */
template<typename T, std::size_t N>
struct printtuple
{
    static std::enable_if_t<std::is_same_v<std::tuple_element_t<N-1, T>, int>, void> ///> Проверка в compile time типов элементов кортежа
    print(const T& tuple)
    {
        printtuple<T, N-1>::print(tuple);
        std::cout << "." << std::get<N-1>(tuple);
        // std::cout <<"\n"<<"print" << __PRETTY_FUNCTION__ << "\n";
    }
};

/**
 * @brief Базовый случай рекурсии вывода элементов кортежа
 * 
 * @tparam T Тип кортежа
 */
template<typename T>
struct printtuple<T, 1>
{
    static std::enable_if_t<std::is_same_v<std::tuple_element_t<0, T>, int>, void>
    print(const T& tuple)
    {   
        std::cout << std::get<0>(tuple);
        //  std::cout <<"\n"<<"print" << __PRETTY_FUNCTION__ << "\n";
    }
};

/**
 * @brief Перегрузка для std::tuple
 * @ingroup print_ip
 * 
 * @warning Элементы выводятся как есть. В случае, если типы кортежа не одинаковы,
 * то ошибка компиляции кода.
 * 
 * @param[in] args std::tuple<...>
 */
template<typename... T>
void print_ip(std::tuple<T...> args)
{  
     // std::cout <<"\n"<<"print" << __PRETTY_FUNCTION__ << "\n";
    printtuple<decltype(args), sizeof...(T)>::print(args);
    std::cout << std::endl;
}
