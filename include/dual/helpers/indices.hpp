#pragma once

#include <cstddef>
#include <type_traits>

namespace dual
{
    /// @brief A variadic template representing a set of indices.
    template <size_t... I>
    struct indices
    {
        /// @brief Defines a template alias that applies a template to a type with indices.
        template <template <class, size_t...> class Type, class T>
        using type = Type<T, I...>;
    };

    /// @brief Checks whether an index exists within a given indices set.
    template <size_t I, class Indices>
    struct has_indice;

    template <size_t I, size_t... Is>
    struct has_indice<I, indices<Is...>>
    {
        static constexpr auto value = ((I == Is) || ...);
    };

    namespace impl
    {
        /// @brief Helper struct for computing a unique set of indices.
        template <class I, class Iout>
        struct indices_set;

        template <size_t... Iout>
        struct indices_set<indices<>, indices<Iout...>>
        {
            using type = indices<Iout...>;
        };

        template <size_t I, size_t... Is, size_t... Iout>
        struct indices_set<indices<I, Is...>, indices<Iout...>>
        {
            using type = std::conditional_t<
                has_indice<I, indices<Iout...>>::value,
                typename indices_set<indices<Is...>, indices<Iout...>>::type,
                typename indices_set<indices<Is...>, indices<Iout..., I>>::type>;
        };
    } // namespace impl

    /// @brief Computes the unique set of indices from a given indices set.
    template <class Indices>
    using indices_set_t = typename impl::indices_set<Indices, indices<>>::type;

    namespace impl
    {
        /// @brief Computes the intersection of two indices sets.
        template <class Ia, class Ib, class Iout>
        struct indices_interception;

        template <size_t... Ib, size_t... Iout>
        struct indices_interception<indices<>, indices<Ib...>, indices<Iout...>>
        {
            using type = indices<Iout...>;
        };

        template <size_t I, size_t... Ia, size_t... Ib, size_t... Iout>
        struct indices_interception<indices<I, Ia...>, indices<Ib...>, indices<Iout...>>
        {
            using type = std::conditional_t<
                has_indice<I, indices<Ib...>>::value,
                typename indices_interception<indices<Ia...>, indices<Ib...>, indices<Iout..., I>>::type,
                typename indices_interception<indices<Ia...>, indices<Ib...>, indices<Iout...>>::type>;
        };
    } // namespace impl

    /// @brief Computes the intersection of two indices sets.
    template <class IndicesA, class IndicesB>
    using indices_interception_t = typename impl::indices_interception<IndicesA, IndicesB, indices<>>::type;

    namespace impl
    {
        /// @brief Computes the union of two indices sets.
        template <class Ia, class Ib>
        struct indices_union;

        template <size_t... Ia, size_t... Ib>
        struct indices_union<indices<Ia...>, indices<Ib...>>
        {
            using type = indices_set_t<indices<Ia..., Ib...>>;
        };
    } // namespace impl

    /// @brief Computes the union of two indices sets.
    template <class IndicesA, class IndicesB>
    using indices_union_t = typename impl::indices_union<IndicesA, IndicesB>::type;

    namespace impl
    {
        /// @brief Computes the difference between two indices sets.
        template <class Ia, class Ib, class Iout>
        struct indices_difference;

        template <size_t... Ib, size_t... Iout>
        struct indices_difference<indices<>, indices<Ib...>, indices<Iout...>>
        {
            using type = indices<Iout...>;
        };

        template <size_t I, size_t... Ia, size_t... Ib, size_t... Iout>
        struct indices_difference<indices<I, Ia...>, indices<Ib...>, indices<Iout...>>
        {
            using type = std::conditional_t<
                has_indice<I, indices<Ib...>>::value,
                typename indices_difference<indices<Ia...>, indices<Ib...>, indices<Iout...>>::type,  ///< Skip I if in B
                typename indices_difference<indices<Ia...>, indices<Ib...>, indices<Iout..., I>>::type>; ///< Keep I otherwise
        };
    } // namespace impl

    /// @brief Computes the difference between two indices sets.
    template <class IndicesA, class IndicesB>
    using indices_difference_t = typename impl::indices_difference<IndicesA, IndicesB, indices<>>::type;

} // namespace dual
