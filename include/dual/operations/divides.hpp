#pragma once

#include "dual/operations.hpp"

namespace dual
{
/// @brief Implements division operation for dual numbers.
/// @tparam T The underlying data type (e.g., float, double).
template <class T>
struct divides : binary_operation<T, divides<T>>
{
    /// @brief Computes the value of the division.
    /// @param v1 Numerator.
    /// @param v2 Denominator.
    /// @return Result of v1 / v2.
    auto value(const T &v1, const T &v2) const
    {
        return v1 / v2;
    }

    /// @brief Computes the derivative of the division operation.
    /// @param n1 The first dual number (numerator).
    /// @param n2 The second dual number (denominator).
    /// @return The derivative result.
    auto dvalue(const duo<T> &n1, const duo<T> &n2) const
    {
        return (n2.v * n1.d - n1.v * n2.d) / (n2.v * n2.v);
    }

    /// @brief Computes the derivative when the numerator is a scalar.
    /// @param v1 The scalar numerator.
    /// @param n2 The dual number denominator.
    /// @return The derivative result.
    auto dvalue(const T &v1, const duo<T> &n2) const
    {
        return (-v1 * n2.d) / (n2.v * n2.v);
    }

    /// @brief Computes the derivative when the denominator is a scalar.
    /// @param n1 The dual number numerator.
    /// @param v2 The scalar denominator.
    /// @return The derivative result.
    auto dvalue(const duo<T> &n1, const T &v2) const
    {
        return (v2 * n1.d) / (v2 * v2);
    }
}; // namespace dual

/// @brief Overloaded division operator for dual numbers and scalars.
/// @tparam T The underlying data type.
/// @tparam D Variadic parameter pack representing differentiation indices.
/// @param n1 The dual number numerator.
/// @param n2 The scalar denominator.
/// @return The result of the division.
template <class T, size_t... D>
inline auto operator/(const number<T, D...> &n1, const T &n2)
{
    return std::invoke(divides<T>{}, n1, n2);
}

/// @brief Overloaded division operator for scalars and dual numbers.
/// @tparam T The underlying data type.
/// @tparam N Type of the scalar numerator.
/// @tparam D Variadic parameter pack representing differentiation indices.
/// @param n1 The scalar numerator.
/// @param n2 The dual number denominator.
/// @return The result of the division.
template <class T, class N, size_t... D>
inline auto operator/(const N &n1, const number<T, D...> &n2)
{
    return std::invoke(divides<T>{}, n1, n2);
}

} // namespace dual
