#pragma once

#include "dual/array.hpp"

namespace dual
{

template <class F, class... Ts>
inline auto summation(const std::tuple<Ts...> &data, F perdicate)
{
	return apply(
		[&](const auto &... elems) {
			return (apply(perdicate, elems) + ...);
		},
		data);
}

template <class F, class... Ts>
inline auto summation(const array<Ts...> &data, F perdicate)
{
	return apply(
		[&](const auto &... elems) {
			return (apply(perdicate, elems) + ...);
		},
		data.storage());
}

} // namespace dual
