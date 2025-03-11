#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
/// @brief Represents the exponential function as a unary operation.
/// @tparam T The type of the number being operated on.
template <class T>
struct exp : unary_operation<T, exp<T>>
{
    /// @brief Computes the exponential value of the input.
    /// @param v The input value.
    /// @return The computed exponential value.
    auto value(const T &v) const
    {
        return std::exp(v);
    }

    /// @brief Computes the derivative of the exponential function.
    /// @param n A duo struct containing the value and its derivative.
    /// @return The computed derivative of the exponential function.
    auto dvalue(const duo<T> &n) const
    {
        return std::exp(n.v) * n.d;
    }
};
} // namespace dual

namespace std
{
/// @brief Computes the exponential function for a dual number.
/// @tparam T The type of the number.
/// @tparam D Parameter pack representing derivative indices.
/// @param n The dual number input.
/// @return The exponential of the given dual number.
template <class T, size_t... D>
inline auto exp(const dual::number<T, D...> &n)
{
    return std::invoke(dual::exp<T>{}, n);
}
}; // namespace std
