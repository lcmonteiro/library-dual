#pragma once

#include "dual/array.hpp"

namespace dual
{

template <class F, class T, std::size_t N>
inline auto apply(F perdicate, const std::array<T, N> &data)
{
	return std::apply(perdicate, data);
}

template <class F, class... Ts>
inline auto apply(F perdicate, const array<Ts...> &data)
{
	return std::apply(perdicate, data.storage());
}

template <class F, class... Ts>
inline auto apply(F perdicate, const std::tuple<Ts...> &data)
{
	return std::apply(perdicate, data);
}

template <class F, class T>
inline auto apply(F perdicate, const T &data)
{
	return std::invoke(perdicate, data);
}

} // namespace dual