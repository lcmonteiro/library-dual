#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
struct pow : binary_operation<pow>
{
	template <class T>
	auto value(const T &v1, const T &v2) const
	{
		return std::pow(v1, v2);
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const duo<T> &n2) const
	{
		return std::pow(n1.v, n2.v - 1) * (n2.v * n1.d + n1.v * n2.d * std::log(n1.v));
	}
	template <class T>
	auto dvalue(const T &v1, const duo<T> &n2) const
	{
		return n2.d * std::pow(v1, n2.v) * std::log(v1);
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const T &v2) const
	{
		return v2 * std::pow(n1.v, v2 - 1) * n1.d;
	}
};

} // namespace dual

namespace std
{
template <class T1, class T2, dual::pow::enable_t<T1, T2> = 0>
inline auto pow(const T1 &n1, const T2 &n2)
{
	return std::invoke(dual::pow{}, n1, n2);
}
} // namespace std

namespace dual
{
struct pow_transform : transform_binary_operation<pow_transform>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return std::pow(n1, n2);
	}
};
} // namespace dual

namespace std
{
template <class T1, class T2, dual::pow_transform::enable_t<T1, T2> = 0>
inline auto pow(const T1 &n1, const T2 &n2)
{
	return std::invoke(dual::pow_transform{}, n1, n2);
}
} // namespace std

namespace dual
{
struct pow_broadcast : broadcast_operation<pow_broadcast>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return std::pow(n1, n2);
	}
};
} // namespace dual

namespace std
{
template <class T1, class T2, dual::pow_broadcast::enable_t<T1, T2> = 0>
inline auto pow(const T1 &c1, const T2 &c2)
{
	return std::invoke(dual::pow_broadcast{}, c1, c2);
}
} // namespace std
