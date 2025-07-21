#pragma once

#include <cmath>
#include <limits>

#include "dual/operations.hpp"

namespace dual
{
struct log : unary_operation<log>
{
	template <class T>
	auto value(const T &v) const
	{
		return std::log(v);
	}
	template <class T>
	auto dvalue(const duo<T> &n) const
	{
		// If the input is invalid for logarithm (n.v <= 0), 
		// the derivative should also be NaN
		if (n.v < static_cast<T>(0)) {
			return std::numeric_limits<T>::quiet_NaN();
		}
		return n.d / n.v;  // This handles n.v == 0 case naturally (produces inf)
	}
};
} // namespace dual

namespace std
{
template <class T, dual::log::enable_t<T> = 0>
inline auto log(const T &n)
{
	return std::invoke(dual::log{}, n);
}
} // namespace std

namespace dual
{
struct log_transform : transform_unary_operation<log_transform>
{
	template <class T>
	auto transform(const T &n) const
	{
		return std::log(n);
	}
};
} // namespace dual

namespace std
{
template <class T, dual::log_transform::enable_t<T> = 0>
inline auto log(const T &n)
{
	return std::invoke(dual::log_transform{}, n);
}
} // namespace std
