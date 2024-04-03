#pragma once
#include <type_traits>
#include <iterator>
namespace lidar::utilities{
     template <typename T, typename = void>
     struct is_iterable : std::false_type {};

     template <typename T>
     struct is_iterable<T, std::void_t<
                                       decltype(std::begin(std::declval<T&>())),
                                       decltype(std::end(std::declval<T&>()))
                                      >
                       > : std::true_type {};

     template <typename T>
     constexpr bool is_iterable_v = is_iterable<T>::value;


     template<typename T, typename = void>
     struct is_byte_iterator : std::false_type {};

     template<typename T>
     struct is_byte_iterator<T, std::void_t<
                                             typename std::iterator_traits<T>::value_type
                                            >
                            > : std::disjunction<
                                                 std::is_same<typename std::iterator_traits<T>::value_type, char>,
                                                 std::is_same<typename std::iterator_traits<T>::value_type, unsigned char>
                                                > {};

}


