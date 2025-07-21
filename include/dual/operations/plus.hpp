#pragma once

#include "dual/operations.hpp"

namespace dual
{
struct plus : binary_operation<plus>
{
	template <class T>
	auto value(const T &v1, const T &v2) const
	{
		return v1 + v2;
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const duo<T> &n2) const
	{
		return n1.d + n2.d;
	}
	template <class T>
	auto dvalue(const T &, const duo<T> &n2) const
	{
		return n2.d;
	}
	template <class T>
	auto dvalue(const duo<T> &n1, const T &) const
	{
		return n1.d;
	}
};
template <class T1, class T2, plus::enable_t<T1, T2> = 0>
inline auto operator+(const T1 &n1, const T2 &n2)
{
	return std::invoke(plus{}, n1, n2);
}

struct plus_transform : transform_binary_operation<plus_transform>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return n1 + n2;
	}
};
template <class T1, class T2, plus_transform::enable_t<T1, T2> = 0>
inline auto operator+(const T1 &c1, const T2 &c2)
{
	return std::invoke(plus_transform{}, c1, c2);
}

struct plus_broadcast : broadcast_operation<plus_broadcast>
{
	template <class T1, class T2>
	auto transform(const T1 &n1, const T2 &n2) const
	{
		return n1 + n2;
	}
};
template <class T1, class T2, plus_broadcast::enable_t<T1, T2> = 0>
inline auto operator+(const T1 &c1, const T2 &c2)
{
	return std::invoke(plus_broadcast{}, c1, c2);
}

} // namespace dual
