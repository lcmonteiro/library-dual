#pragma once

#include "dual/operations.hpp"

namespace dual
{
struct minus : binary_operation<minus>
{
	template <class T>
	auto value(const T &v1, const T &v2) const
	{
		return v1 - v2;
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const duo<T> &n2) const
	{
		return n1.d - n2.d;
	}
	template <class T>
	auto dvalue(const T &, const duo<T> &n2) const
	{
		return -n2.d;
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const T &) const
	{
		return n1.d;
	}
};
template <class T1, class T2, minus::enable_t<T1, T2> = 0>
inline auto operator-(const T1 &n1, const T2 &n2)
{
	return std::invoke(minus{}, n1, n2);
}

struct minus_transform : transform_binary_operation<minus_transform>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return n1 - n2;
	}
};
template <class T1, class T2, class = minus_transform::enable_t<T1, T2>>
inline auto operator-(const T1 &c1, const T2 &c2)
{
	return std::invoke(minus_transform{}, c1, c2);
}

struct minus_broadcast : broadcast_operation<minus_broadcast>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return n1 - n2;
	}
};
template <class T1, class T2, minus_broadcast::enable_t<T1, T2> = 0>
inline auto operator-(const T1 &c1, const T2 &c2)
{
	return std::invoke(minus_broadcast{}, c1, c2);
}

} // namespace dual
