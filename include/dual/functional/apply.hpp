#pragma once

#include "dual/array.hpp"

namespace dual
{

template <class F, class T, std::size_t N>
inline auto apply(F predicate, const std::array<T, N> &data)
{
	return std::apply(predicate, data);
}

template <class F, class... Ts>
inline auto apply(F predicate, const array<Ts...> &data)
{
	return std::apply(predicate, data.storage());
}

template <class F, class... Ts>
inline auto apply(F predicate, const std::tuple<Ts...> &data)
{
	return std::apply(predicate, data);
}

template <class F, class T>
inline auto apply(F predicate, const T &data)
{
	return std::invoke(predicate, data);
}

} // namespace dual