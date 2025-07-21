#pragma once

#include "dual/functional/view.hpp"

namespace dual
{
    
template <class... Containers>
constexpr auto concat(Containers &... cs)
{
	return array(std::tuple_cat(view(cs).storage()...));
}

template <class... Containers>
constexpr auto concat(const Containers &... cs)
{
	return array(std::tuple_cat(cs.storage()...));
}

} // namespace dual
