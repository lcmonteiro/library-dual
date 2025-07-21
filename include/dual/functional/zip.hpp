#pragma once

#include <tuple>

#include "helpers/indices.hpp"

namespace dual
{
    
namespace details
{
template <size_t I, class... Ts>
constexpr auto zip(const Ts &... containers)
{
	return std::tie(std::get<I>(containers)...);
}
} // namespace details

template <size_t... Is, class... Ts>
constexpr auto zip(indices<Is...>, const Ts &... containers)
{
	return std::tuple(details::zip<Is>(containers...)...);
}

template <class... Ts>
constexpr auto zip(const Ts &... containers)
{
	constexpr auto N = std::min({std::tuple_size_v<Ts>...});
	return zip(indices_sequence_t<0, N>{}, containers...);
}

} // namespace dual
