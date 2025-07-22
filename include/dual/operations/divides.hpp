#pragma once

#include "dual/operations.hpp"

namespace dual
{
struct divides : binary_operation<divides>
{
	template <class T>
	auto value(const T &v1, const T &v2) const
	{
		return v1 / v2;
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const duo<T> &n2) const
	{
		return (n2.v * n1.d - n1.v * n2.d) / (n2.v * n2.v);
	}
	template <class T>
	auto dvalue(const T &v1, const duo<T> &n2) const
	{
		return (-v1 * n2.d) / (n2.v * n2.v);
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const T &v2) const
	{
		return (v2 * n1.d) / (v2 * v2);
	}
};
template <class T1, class T2, divides::enable_t<T1, T2> = 0>
inline auto operator/(const T1 &n1, const T2 &n2)
{
	return std::invoke(divides{}, n1, n2);
}

struct divides_transform : transform_binary_operation<divides_transform>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return n1 / n2;
	}
};
template <class T1, class T2, class = divides_transform::enable_t<T1, T2>>
inline auto operator/(const T1 &c1, const T2 &c2)
{
	return std::invoke(divides_transform{}, c1, c2);
}

struct divides_broadcast : broadcast_operation<divides_broadcast>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return n1 / n2;
	}
};
template <class T1, class T2, divides_broadcast::enable_t<T1, T2> = 0>
inline auto operator/(const T1 &c1, const T2 &c2)
{
	return std::invoke(divides_broadcast{}, c1, c2);
}

} // namespace dual
