#pragma once

#include <functional>

#include "array.hpp"

namespace dual
{
/// @brief Structure representing a dual number with a value and derivative.
/// @tparam T The data type of the value and derivative.
template <class T>
struct duo
{
    const T &v; ///< The value.
    const T &d; ///< The derivative.
};
/// @brief Creates a duo object from a number.
/// @tparam D The differentiation order.
/// @tparam T The data type of the number.
/// @tparam Dn Additional differentiation orders.
/// @param n The number object.
/// @return A duo object containing the value and derivative.
template <std::size_t D, class T, std::size_t... Dn>
inline auto make_duo(const number<T, Dn...> &n)
{
    return duo<T>{n.value(), n.template dvalue<D>()};
}
/// @brief Base class for unary operations on numbers.
/// @tparam Derived The derived class implementing the operation.
template <class Derived>
struct unary_operation
{
    template <class T>
    using enable_t = std::enable_if_t<is_number_v<T>, int>;

    /// @brief Applies the unary operation to a number.
    /// @tparam T The data type of the number.
    /// @tparam D1 Differentiation orders.
    /// @param n1 The input number.
    /// @return The result of the operation.
    template <class T, std::size_t... D1>
    auto operator()(const number<T, D1...> &n1) const
    {
        auto result = number<T, D1...>{};
        update_value(n1.value(), result);
        update_dvalues(indices<D1...>{}, n1, result);
        return result;
    }

  protected:
    /// @brief Retrieves the derived class instance.
    /// @return Pointer to the derived class.
    auto self() const
    {
        return static_cast<const Derived *>(this);
    }

    /// @brief Updates the value of the result.
    /// @tparam N The result number type.
    /// @param v1 The input value.
    /// @param n The result number.
    template <class T, class N>
    void update_value(const T &v1, N &n) const
    {
        n.value(self()->value(v1));
    }

    /// @brief Updates the derivative value of the result.
    /// @tparam D The differentiation order.
    /// @tparam N The number type.
    /// @param n1 The input number.
    /// @param n The result number.
    template <std::size_t D, class N>
    void update_dvalue(const N &n1, N &n) const
    {
        n.template dvalue<D>(self()->dvalue(make_duo<D>(n1)));
    }

  private:
    /// @brief Updates all derivative values.
    /// @tparam Dn Differentiation orders.
    /// @tparam N The number type.
    /// @param n1 The input number.
    /// @param n The result number.
    template <std::size_t... Dn, class N>
    void update_dvalues(const indices<Dn...>, const N &n1, N &n) const
    {
        (update_dvalue<Dn>(n1, n), ...);
    }
};

template <class N1, class N2>
struct binary_operation_indices
{
    using common = indices_interception_t<N1, N2>;
    using only_1 = indices_difference_t<N1, common>;
    using only_2 = indices_difference_t<N2, common>;
    using result = indices_concat_t<only_1, common, only_2>;
};

/// @brief Base class for binary operations on numbers.
/// @tparam Derived The derived class implementing the operation.
template <class Derived>
struct binary_operation
{
    template <class T1, class T2>
    using enable_t = std::enable_if_t<
        ((is_number_v<T1> and is_number_like_v<T2>) or
         (is_number_v<T2> and is_number_like_v<T1>)),
        int>;

    /// @brief Applies the binary operation to a number and a scalar.
    /// @tparam T The data type of the number.
    /// @tparam D1 Differentiation orders.
    /// @param n1 The input number.
    /// @param v2 The scalar value.
    /// @return The result of the operation.
    template <class T, std::size_t... D1>
    auto operator()(const number<T, D1...> &n1, const T &v2) const
    {
        auto result = number<T, D1...>{};
        update_value(n1.value(), v2, result);
        update_dvalues(indices<D1...>{}, n1, v2, result);
        return result;
    }

    /// @brief Applies the binary operation to a scalar and a number.
    /// @tparam T The data type of the number.
    /// @tparam D2 Differentiation orders.
    template <class T, std::size_t... D2>
    auto operator()(const T &v1, const number<T, D2...> &n2) const
    {
        auto result = number<T, D2...>{};
        update_value(v1, n2.value(), result);
        update_dvalues(indices<D2...>{}, v1, n2, result);
        return result;
    }

    /// @brief Applies the binary operation to two numbers.
    /// @tparam T The data type of the number.
    /// @tparam D1 Differentiation orders.
    /// @tparam D2 Differentiation orders.
    template <class T, std::size_t... D1, std::size_t... D2>
    auto operator()(const number<T, D1...> &n1, const number<T, D2...> &n2) const
    {
        using indices = binary_operation_indices<indices<D1...>, indices<D2...>>;
        using result_type = typename indices::result::template type<number, T>;
        auto result = result_type{};
        update_value(n1.value(), n2.value(), result);
        update_dvalues(typename indices::only_1{}, n1, n2.value(), result);
        update_dvalues(typename indices::only_2{}, n1.value(), n2, result);
        update_dvalues(typename indices::common{}, n1, n2, result);
        return result;
    }

  protected:
    /// @brief Retrieves the derived class instance.
    auto self() const
    {
        return static_cast<const Derived *>(this);
    }

    /// @brief Updates the value of the result.
    template <class T, class N>
    void update_value(const T &v1, const T &v2, N &n) const
    {
        n.value(self()->value(v1, v2));
    }

    /// @brief Updates the derivative values.
    template <std::size_t D, class N1, class N2, class N>
    void update_dvalue(const N1 &n1, const N2 &n2, N &n) const
    {
        if constexpr (not is_number_v<N1>)
        {
            n.template dvalue<D>(self()->dvalue(n1, make_duo<D>(n2)));
        }
        else if constexpr (not is_number_v<N2>)
        {
            n.template dvalue<D>(self()->dvalue(make_duo<D>(n1), n2));
        }
        else
        {
            n.template dvalue<D>(self()->dvalue(make_duo<D>(n1), make_duo<D>(n2)));
        }
    }

  private:
    template <std::size_t... Dn, class N1, class N2, class N>
    void update_dvalues(const indices<Dn...>, const N1 &n1, const N2 &n2, N &n) const
    {
        (update_dvalue<Dn>(n1, n2, n), ...);
    }
};

template <class Derived>
struct transform_unary_operation
{
    template <class T>
    using enable_t = std::enable_if_t<is_array_v<T>, int>;

    template <class... T>
    auto operator()(const array<T...> &c) const
    {
        return transform(c, c.indices());
    }

  protected:
    auto self() const
    {
        return static_cast<const Derived *>(this);
    }

    template <class T, std::size_t... Is>
    auto transform(const T &c, indices<Is...>) const
    {
        return array{self()->transform(std::get<Is>(c))...};
    }
};

template <class Derived>
struct transform_binary_operation
{
    template <class T1, class T2>
    using enable_t = std::enable_if_t<
        ((is_array_v<T1> and is_array_like_v<T2>) or
         (is_array_v<T2> and is_array_like_v<T1>)),
        int>;

    template <class... T1, class T2>
    auto operator()(const array<T1...> &c1, const T2 &c2) const
    {
        return transform(c1, c2, c1.indices());
    }

    template <class T1, class... T2>
    auto operator()(const T1 &c1, const array<T2...> &c2) const
    {
        return transform(c1, c2, c2.indices());
    }

    template <class... T1, class... T2>
    auto operator()(const array<T1...> &c1, const array<T2...> &c2) const
    {
        return transform(c1, c2, c2.indices());
    }

  protected:
    auto self() const
    {
        return static_cast<const Derived *>(this);
    }

    template <class T1, class T2, std::size_t... Is>
    auto transform(const T1 &c1, const T2 &c2, indices<Is...>) const
    {
        return array{self()->transform(
            std::get<Is>(c1),
            std::get<Is>(c2))...};
    }
};

template <class Derived>
struct broadcast_operation
{
    template <class T1, class T2>
    using enable_t = std::enable_if_t<
        ((is_array_v<T1> and is_number_like_v<T2>) or
         (is_array_v<T2> and is_number_like_v<T1>)),
        int>;

    template <class... T1, class T2>
    auto operator()(const array<T1...> &c1, const T2 &c2) const
    {
        return transform(c1, c2, c1.indices());
    }

    template <class T1, class... T2>
    auto operator()(const T1 &c1, const array<T2...> &c2) const
    {
        return transform(c1, c2, c2.indices());
    }

  protected:
    auto self() const
    {
        return static_cast<const Derived *>(this);
    }

    template <class... T1, class T2, std::size_t... Is>
    auto transform(const array<T1...> &c1, const T2 &c2, indices<Is...>) const
    {
        return array{self()->transform(std::get<Is>(c1), c2)...};
    }

    template <class T1, class... T2, std::size_t... Is>
    auto transform(const T1 &c1, const array<T2...> &c2, indices<Is...>) const
    {
        return array{self()->transform(c1, std::get<Is>(c2))...};
    }
};

} // namespace dual
