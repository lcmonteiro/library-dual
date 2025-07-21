#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
struct sin : unary_operation<sin>
{
	template <class T>
	auto value(const T &v) const
	{
		return std::sin(v);
	}
	template <class T>
	auto dvalue(const duo<T> &n) const
	{
		return std::cos(n.v) * n.d;
	}
};
} // namespace dual

namespace std
{
template <class T, dual::sin::enable_t<T> = 0>
inline auto sin(const T &n)
{
	return std::invoke(dual::sin{}, n);
}
} // namespace std

namespace dual
{
struct sin_transform : transform_unary_operation<sin_transform>
{
	template <class T>
	auto transform(const T &n) const
	{
		return std::sin(n);
	}
};
} // namespace dual

namespace std
{
template <class T, dual::sin_transform::enable_t<T> = 0>
inline auto sin(const T &n)
{
	return std::invoke(dual::sin_transform{}, n);
}
} // namespace std
