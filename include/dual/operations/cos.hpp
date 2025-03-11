#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
    /// @brief Computes the cosine of a given value and its derivative.
    /// @tparam T The numeric type of the value.
    template <class T>
    struct cos : unary_operation<T, cos<T>>
    {
        /// @brief Computes the cosine of a value.
        /// @param v The input value.
        /// @return The cosine of v.
        auto value(const T &v) const
        {
            return std::cos(v);
        }

        /// @brief Computes the derivative of the cosine function.
        /// @param n A duo containing the input value and its derivative.
        /// @return The derivative of cos(n.v), which is -sin(n.v) * n.d.
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
    /// @tparam D Variadic template parameter representing derivative indices.
    /// @param n The dual number.
    /// @return The cosine of the dual number.
    template <class T, size_t... D>
    inline auto cos(const dual::number<T, D...> &n)
    {
        return std::invoke(dual::cos<T>{}, n);
    }
} // namespace std
