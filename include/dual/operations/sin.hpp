#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
/// @brief Represents the sine function as a unary operation.
///
/// This struct implements the sine function for dual numbers, allowing for
/// differentiation of expressions involving sine.
///
/// @tparam T The underlying numerical type.
template <class T>
struct sin : unary_operation<T, sin<T>>
{
    /// @brief Computes the sine of a value.
    /// @param v The input value.
    /// @return The sine of v.
    auto value(const T &v) const
    {
        return std::sin(v);
    }

    /// @brief Computes the derivative of the sine function.
    /// @param n The dual number input.
    /// @return The derivative of the sine function, which is cos(v) * dv.
    auto dvalue(const duo<T> &n) const
    {
        return std::cos(n.v) * n.d;
    }
};

} // namespace dual

namespace std
{
/// @brief Overload of the sine function for dual numbers.
/// @tparam T The numerical type.
/// @tparam D Parameter pack representing derivative indices.
/// @param n The dual number input.
/// @return The sine of the dual number.
template <class T, size_t... D>
inline auto sin(const dual::number<T, D...> &n)
{
    return std::invoke(dual::sin<T>{}, n);
}

} // namespace std
