#pragma once

#include "dual/functional/apply.hpp"

namespace dual
{

template <class F, class... Ts>
inline auto for_each(const std::tuple<Ts...> &data, F process)
{
	apply(
		[&](const auto &... elems) {
			(apply(process, elems), ...);
		},
		data);
}

template <class F, class... Ts>
inline auto for_each(const array<Ts...> &data, F process)
{
	apply(
		[&](const auto &... elems) {
			(apply(process, elems), ...);
		},
		data.storage());
}

} // namespace dual
