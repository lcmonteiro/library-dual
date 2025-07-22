#pragma once

#include "dual/operations.hpp"

namespace dual
{
struct unary_minus : unary_operation<unary_minus>
{
	template <class T>
	auto value(const T &v) const
	{
		return -v;
	}
	
	template <class T>
	auto dvalue(const duo<T> &n) const
	{
		return -n.d;
	}
};

template <class T, unary_minus::enable_t<T> = 0>
inline auto operator-(const T &n)
{
	return std::invoke(unary_minus{}, n);
}

struct unary_minus_transform : transform_unary_operation<unary_minus_transform>
{
	template <class T>
	auto transform(const T &n) const
	{
		return -n;
	}
};

template <class T, unary_minus_transform::enable_t<T> = 0>
inline auto operator-(const T &n)
{
	return std::invoke(unary_minus_transform{}, n);
}

} // namespace dual