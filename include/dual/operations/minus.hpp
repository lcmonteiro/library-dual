#pragma once

#include "dual/operations.hpp"

namespace dual
{
/// @brief Represents the subtraction operation as a binary operation.
/// @tparam T The type of the number being operated on.
template <class T>
struct minus : binary_operation<T, minus<T>>
{
    /// @brief Computes the result of subtracting two values.
    /// @param v1 The first value.
    /// @param v2 The second value.
    /// @return The result of v1 - v2.
    auto value(const T &v1, const T &v2) const
    {
        return v1 - v2;
    }

    /// @brief Computes the derivative of the subtraction operation.
    /// @param n1 The first duo containing value and derivative.
    /// @param n2 The second duo containing value and derivative.
    /// @return The computed derivative of the subtraction.
    auto dvalue(const duo<T> &n1, const duo<T> &n2) const
    {
        return n1.d - n2.d;
    }

    /// @brief Computes the derivative when subtracting a duo from a scalar.
    /// @param n2 The duo struct containing the value and its derivative.
    /// @return The computed derivative.
    auto dvalue(const T &, const duo<T> &n2) const
    {
        return -n2.d;
    }

    /// @brief Computes the derivative when subtracting a scalar from a duo.
    /// @param n1 The duo struct containing the value and its derivative.
    /// @return The computed derivative.
    auto dvalue(const duo<T> &n1, const T &) const
    {
        return n1.d;
    }
};

/// @brief Overloads the subtraction operator for a scalar and a dual number.
/// @tparam T The type of the number.
/// @tparam N The type of the scalar.
/// @tparam D Parameter pack representing derivative indices.
/// @param n1 The scalar value.
/// @param n2 The dual number.
/// @return The result of the subtraction.
template <class T, class N, size_t... D>
inline auto operator-(const N &n1, const number<T, D...> &n2)
{
    return std::invoke(minus<T>{}, n1, n2);
}

/// @brief Overloads the subtraction operator for a dual number and a scalar.
/// @tparam T The type of the number.
/// @tparam D Parameter pack representing derivative indices.
/// @param n1 The dual number.
/// @param n2 The scalar value.
/// @return The result of the subtraction.
template <class T, size_t... D>
inline auto operator-(const number<T, D...> &n1, const T &n2)
{
    return std::invoke(minus<T>{}, n1, n2);
}

} // namespace dual
