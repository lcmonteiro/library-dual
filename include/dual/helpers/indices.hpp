#pragma once

#include <type_traits>
#include <utility>

namespace dual
{
template <size_t... I>
struct indices
{
    template <
        template <class, size_t...>
        class Type,
        class T>
    using type = Type<T, I...>;
};

template <size_t... A, size_t... B>
constexpr auto operator+(indices<A...>, indices<B...>)
{
    return indices<A..., B...>{};
}

template <size_t I, size_t... Is>
constexpr bool contains = ((I == Is) || ...);

// ========== FILTER ================
namespace impl
{
template <class Indices, template <size_t> class Predicate>
struct indices_filter;

template <template <size_t> class Predicate, size_t... Is>
struct indices_filter<indices<Is...>, Predicate>
{
    template <size_t I>
    using wrap_if = std::conditional_t<Predicate<I>::value, indices<I>, indices<>>;
    using type = decltype((indices<>{} + ... + wrap_if<Is>{}));
};
} // namespace impl

template <class Indices, template <size_t> class Predicate>
using indices_filter_t = typename impl::indices_filter<Indices, Predicate>::type;

// ========== INTERSECTION ==========
namespace impl
{
template <class IndicesA, class IndicesB>
struct intersection;

template <size_t... Ia, size_t... Ib>
struct intersection<indices<Ia...>, indices<Ib...>>
{
    template <size_t I>
    using in_b = std::bool_constant<contains<I, Ib...>>;
    using type = indices_filter_t<indices<Ia...>, in_b>;
};
} // namespace impl
template <class IndicesA, class IndicesB>
using indices_interception_t = typename impl::intersection<IndicesA, IndicesB>::type;

// ========== DIFFERENCE ==========
namespace impl
{
template <class IndicesA, class IndicesB>
struct difference;

template <size_t... Ia, size_t... Ib>
struct difference<indices<Ia...>, indices<Ib...>>
{
    template <size_t I>
    using not_in_b = std::bool_constant<!contains<I, Ib...>>;
    using type = indices_filter_t<indices<Ia...>, not_in_b>;
};
} // namespace impl

template <class IndicesA, class IndicesB>
using indices_difference_t = typename impl::difference<IndicesA, IndicesB>::type;

// ========== CONCAT ==========
namespace impl
{
template <class Ia, class Ib, class Ic>
struct indices_concat;

template <size_t... Ia, size_t... Ib, size_t... Ic>
struct indices_concat<indices<Ia...>, indices<Ib...>, indices<Ic...>>
{
    using type = indices<Ia..., Ib..., Ic...>;
};

} // namespace impl

template <class IndicesA, class IndicesB, class IndicesC>
using indices_concat_t = typename impl::indices_concat<IndicesA, IndicesB, IndicesC>::type;

// ========== SEQUENCE ==========
namespace impl
{
template <std::size_t StartSeq, class IndexSeq>
struct indices_sequence;

template <std::size_t Start, std::size_t... Indices>
struct indices_sequence<Start, std::index_sequence<Indices...>>
{
    using type = indices<(Start + Indices)...>;
};
} // namespace impl

template <std::size_t Start, std::size_t Size>
using indices_sequence_t =
    typename impl::indices_sequence<Start, std::make_index_sequence<Size>>::type;

template <std::size_t Start, class... Ts>
using indices_sequence_for_t = indices_sequence_t<Start, sizeof...(Ts)>;

} // namespace dual
