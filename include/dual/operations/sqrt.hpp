#pragma once

#include <cmath>

#include "dual/operations.hpp"

namespace dual
{
struct sqrt : unary_operation<sqrt>
{
    template <class T>
    auto value(const T &v) const
    {
        return std::sqrt(v);
    }

    template <class T>
    auto dvalue(const duo<T> &n) const
    {
        return n.d / (static_cast<T>(2.0) * std::sqrt(n.v));
    }
};
} // namespace dual

namespace std
{
template <class T, dual::sqrt::enable_t<T> = 0>
inline auto sqrt(const T &n)
{
    return std::invoke(dual::sqrt{}, n);
}
} // namespace std

namespace dual
{
struct sqrt_transform : transform_unary_operation<sqrt_transform>
{
    template <class T>
    auto transform(const T &n) const
    {
        return std::sqrt(n);
    }
};
} // namespace dual

namespace std
{
template <class T, dual::sqrt_transform::enable_t<T> = 0>
inline auto sqrt(const T &n)
{
    return std::invoke(dual::sqrt_transform{}, n);
}
} // namespace std
