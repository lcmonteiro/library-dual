#pragma once

#include <iostream>

#include "dual/array.hpp"
#include "dual/number.hpp"

namespace dual
{

template <class U, size_t... Is>
inline auto print(const number<U, Is...> &n);

template <class...U>
inline auto print(const array<U...> &data);

template<class U>
inline auto print(const U & value);

template <class U, class... Us>
inline auto print(const U &value, const Us &... values);

template <class U, size_t N>
inline auto print(const std::array<U, N> &data);


template <class U, size_t... Is>
inline auto print(const number<U, Is...> &n)
{
	std::cout << n.value() << " [";
	((std::cout << Is << ":" << n.template dvalue<Is>() << " "), ...);
	std::cout << "]" << std::endl;
}

template <class...U>
inline auto print(const array<U...> &data)
{
	std::apply([](auto &... v) { print(v...); }, data.storage());
}

template <class U, size_t N>
inline auto print(const std::array<U, N> &data)
{
	std::apply([](auto &... v) { print(v...); }, data);
}

template<class U>
inline auto print(const U &value)
{
	std::cout << value << std::endl;
}

template <class U, class... Us>
inline auto print(const U &value, const Us &... values)
{
	print(value);
	(print(values), ...);
}

} // namespace dual
