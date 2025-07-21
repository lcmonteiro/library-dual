#pragma once

#include "dual/array.hpp"

namespace dual
{

template <size_t... Is, class... Ts>
constexpr auto view(indices<Is...>, array<Ts...> &data)
{
	return array(std::tie(std::get<Is>(data)...));
}

template <class... Ts>
constexpr auto view(array<Ts...> &data)
{
	return view(data.indices(), data);
}

} // namespace dual
