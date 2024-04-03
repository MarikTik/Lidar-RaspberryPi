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


     template<typename iterator>
     constexpr bool is_byte_iterator() {
          using value_type = typename std::iterator_traits<iterator>::value_type;
          return std::is_same_v<value_type, char> or std::is_same_v<value_type, unsigned char>;
     }
}


