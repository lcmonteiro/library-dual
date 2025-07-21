#pragma once

#include "dual/array.hpp"

namespace dual
{

template <class F, class... Ts>
inline auto summation(const std::tuple<Ts...> &data, F predicate)
{
	return apply(
		[&](const auto &... elems) {
			return (apply(predicate, elems) + ...);
		},
		data);
}

template <class F, class... Ts>
inline auto summation(const array<Ts...> &data, F predicate)
{
	return apply(
		[&](const auto &... elems) {
			return (apply(predicate, elems) + ...);
		},
		data.storage());
}

} // namespace dual
