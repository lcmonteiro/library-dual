#pragma once

#include "dual/operations.hpp"

namespace dual
{
struct negate : unary_operation<negate>
{
    template <class T>
    auto value(const T &v) const
    {
        return -v;
    }
    
    template <class T>
    auto dvalue(const duo<T> &n) const
    {
        return -n.d;
    }
};

template <class T, negate::enable_t<T> = 0>
inline auto operator-(const T &n)
{
    return std::invoke(negate{}, n);
}

struct negate_transform : transform_unary_operation<negate_transform>
{
    template <class T>
    auto transform(const T &n) const
    {
        return -n;
    }
};

template <class T, negate_transform::enable_t<T> = 0>
inline auto operator-(const T &n)
{
    return std::invoke(negate_transform{}, n);
}

} // namespace dual