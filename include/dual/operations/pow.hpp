#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
/// @brief Represents the power function as a binary operation.
///
/// This struct implements the power function for dual numbers, allowing for
/// differentiation of expressions involving exponentiation.
///
/// @tparam T The underlying numerical type.
template <class T>
struct pow : binary_operation<T, pow<T>>
{
    /// @brief Computes the power function.
    /// @param v1 The base value.
    /// @param v2 The exponent value.
    /// @return The result of v1 raised to the power of v2.
    auto value(const T &v1, const T &v2) const
    {
        return std::pow(v1, v2);
    }

    /// @brief Computes the derivative when both the base and exponent are dual numbers.
    /// @param n1 The dual number representing the base.
    /// @param n2 The dual number representing the exponent.
    /// @return The derivative of the power function with respect to both variables.
    auto dvalue(const duo<T> &n1, const duo<T> &n2) const
    {
        return std::pow(n1.v, n2.v - 1) * (n2.v * n1.d + n1.v * n2.d * std::log(n1.v));
    }

    /// @brief Computes the derivative when the base is a scalar and the exponent is a dual number.
    /// @param v1 The scalar base.
    /// @param n2 The dual number exponent.
    /// @return The computed derivative.
    auto dvalue(const T &v1, const duo<T> &n2) const
    {
        return n2.d * std::pow(v1, n2.v) * std::log(v1);
    }

    /// @brief Computes the derivative when the base is a dual number and the exponent is a scalar.
    /// @param n1 The dual number base.
    /// @param v2 The scalar exponent.
    /// @return The computed derivative.
    auto dvalue(const duo<T> &n1, const T &v2) const
    {
        return v2 * std::pow(n1.v, v2 - 1) * n1.d;
    }
};

} // namespace dual

namespace std
{
/// @brief Overload of the power function for a scalar base and a dual number exponent.
/// @tparam T The numerical type.
/// @tparam N The type of the scalar base.
/// @tparam D Parameter pack representing derivative indices.
/// @param n1 The scalar base.
/// @param n2 The dual number exponent.
/// @return The result of the exponentiation.
template <class T, class N, size_t... D>
inline auto pow(const N &n1, const dual::number<T, D...> &n2)
{
    return std::invoke(dual::pow<T>{}, n1, n2);
}

/// @brief Overload of the power function for a dual number base and a scalar exponent.
/// @tparam T The numerical type.
/// @tparam D Parameter pack representing derivative indices.
/// @param n1 The dual number base.
/// @param n2 The scalar exponent.
/// @return The result of the exponentiation.
template <class T, size_t... D>
inline auto pow(const dual::number<T, D...> &n1, const T &n2)
{
    return std::invoke(dual::pow<T>{}, n1, n2);
}

} // namespace std
