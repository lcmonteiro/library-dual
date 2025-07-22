#pragma once

#include "dual/array.hpp"

namespace dual
{

template <class F, class... Ts>
inline auto transform(const array<Ts...> &data, F predicate)
{
	return std::apply(
		[&](const auto &... elems) {
			return array(std::apply(predicate, elems)...);
		},
		data.storage());
}

template <class F, class T, std::size_t N>
inline auto transform(const std::array<T, N> &data, F predicate)
{
	return std::apply(
		[&](const auto &... elems) {
			return std::array{predicate(elems)...};
		},
		data);
}

} // namespace dual
