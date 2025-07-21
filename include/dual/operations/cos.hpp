#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{

/// @brief Computes the cosine of a given value and its derivative.
struct cos : unary_operation<cos>
{
    /// @brief Computes the cosine of a value.
    /// @tparam T The numeric type of the value.
    /// @param v The input value.
    /// @return The cosine of v.
	template <class T>
    auto value(const T &v) const
	{
		return std::cos(v);
	}

    /// @brief Computes the derivative of the cosine function.
    /// @tparam T The numeric type of the value.
    /// @param n A duo containing the input value and its derivative.
    /// @return The derivative of cos(n.v), which is -sin(n.v) * n.d.
	template <class T>
	auto dvalue(const duo<T> &n) const
	{
		return -std::sin(n.v) * n.d;
	}
};
} // namespace dual

namespace std
{
/// @brief Overloads the standard cos function for dual numbers.
/// @tparam T The numeric type.
/// @param n The dual number.
/// @return The cosine of the dual number.
template <class T, dual::cos::enable_t<T> = 0>
inline auto cos(const T &n)
{
	return std::invoke(dual::cos{}, n);
}
} // namespace std

namespace dual
{
struct cos_transform : transform_unary_operation<cos_transform>
{
	template <class T>
	auto transform(const T &n) const
	{
		return std::cos(n);
	}
};
} // namespace dual

namespace std
{
template <class T, dual::cos_transform::enable_t<T> = 0>
inline auto cos(const T &n)
{
	return std::invoke(dual::cos_transform{}, n);
}
} // namespace std
