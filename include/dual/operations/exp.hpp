#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
struct exp : unary_operation<exp>
{
	template <class T>
	auto value(const T &v) const
	{
		return std::exp(v);
	}

	template <class T>
	auto dvalue(const duo<T> &n) const
	{
		return std::exp(n.v) * n.d;
	}
};
} // namespace dual

namespace std
{
template <class T, dual::exp::enable_t<T> = 0>
inline auto exp(const T &n)
{
	return std::invoke(dual::exp{}, n);
}
} // namespace std

namespace dual
{
struct exp_transform : transform_unary_operation<exp_transform>
{
	template <class T>
	auto transform(const T &n) const
	{
		return std::exp(n);
	}
};
} // namespace dual

namespace std
{
template <class T, dual::exp_transform::enable_t<T> = 0>
inline auto exp(const T &n)
{
	return std::invoke(dual::exp_transform{}, n);
}
} // namespace std

