#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
/// @brief Represents the natural logarithm function as a unary operation.
/// @tparam T The type of the number being operated on.
template <class T>
struct log : unary_operation<T, log<T>>
{
    /// @brief Computes the natural logarithm of the input value.
    /// @param v The input value.
    /// @return The computed natural logarithm of v.
    auto value(const T &v) const
    {
        return std::log(v);
    }

    /// @brief Computes the derivative of the natural logarithm function.
    /// @param n A duo struct containing the value and its derivative.
    /// @return The computed derivative of the logarithm function.
    auto dvalue(const duo<T> &n) const
    {
        return n.d / n.v;
    }
};
} // namespace dual

namespace std
{
/// @brief Computes the natural logarithm for a dual number.
/// @tparam T The type of the number.
/// @tparam D Parameter pack representing derivative indices.
/// @param n The dual number input.
/// @return The natural logarithm of the given dual number.
template <class T, size_t... D>
inline auto log(const dual::number<T, D...> &n)
{
    return std::invoke(dual::log<T>{}, n);
}
}; // namespace std
