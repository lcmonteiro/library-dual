#pragma once

#include <functional>

#include "dual/helpers/indices.hpp"
#include "dual/number.hpp"

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
template <size_t D, class T, size_t... Dn>
auto make_duo(const number<T, Dn...> &n)
{
    return duo<T>{n.value(), n.template dvalue<D>()};
}

/// @brief Base class for unary operations on numbers.
/// @tparam T The data type of the number.
/// @tparam Derived The derived class implementing the operation.
template <class T, class Derived>
struct unary_operation
{
    /// @brief Applies the unary operation to a number.
    /// @tparam D1 Differentiation orders.
    /// @param n1 The input number.
    /// @return The result of the operation.
    template <size_t... D1>
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
    template <class N>
    void update_value(const T &v1, N &n) const
    {
        n.value(self()->value(v1));
    }

    /// @brief Updates the derivative value of the result.
    /// @tparam D The differentiation order.
    /// @tparam N The number type.
    /// @param n1 The input number.
    /// @param n The result number.
    template <size_t D, class N>
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
    template <size_t... Dn, class N>
    void update_dvalues(const indices<Dn...>, const N &n1, N &n) const
    {
        (update_dvalue<Dn>(n1, n), ...);
    }
};

/// @brief Base class for binary operations on numbers.
/// @tparam T The data type of the number.
/// @tparam Derived The derived class implementing the operation.
template <class T, class Derived>
struct binary_operation
{
    /// @brief Applies the binary operation to a number and a scalar.
    /// @tparam D1 Differentiation orders.
    /// @param n1 The input number.
    /// @param v2 The scalar value.
    /// @return The result of the operation.
    template <size_t... D1>
    auto operator()(const number<T, D1...> &n1, const T &v2) const
    {
        using indices_result = indices_set_t<indices<D1...>>;
        using result_type = typename indices_result::template type<number, T>;
        auto result = result_type{};
        update_value(n1.value(), v2, result);
        update_dvalues(indices_result{}, n1, v2, result);
        return result;
    }

    /// @brief Applies the binary operation to a scalar and a number.
    template <size_t... D2>
    auto operator()(const T &v1, const number<T, D2...> &n2) const
    {
        using indices_result = indices_set_t<indices<D2...>>;
        using result_type = typename indices_result::template type<number, T>;
        auto result = result_type{};
        update_value(v1, n2.value(), result);
        update_dvalues(indices_result{}, v1, n2, result);
        return result;
    }

    /// @brief Applies the binary operation to two numbers.
    template <size_t... D1, size_t... D2>
    auto operator()(const number<T, D1...> &n1, const number<T, D2...> &n2) const
    {
        using indices_n1 = indices<D1...>;
        using indices_n2 = indices<D2...>;
        using indices_n1_only = indices_difference_t<indices_n1, indices_n2>;
        using indices_n2_only = indices_difference_t<indices_n2, indices_n1>;
        using indices_inner = indices_interception_t<indices_n1, indices_n2>;
        using indices_result = indices_set_t<indices<D1..., D2...>>;
        using result_type = typename indices_result::template type<number, T>;
        auto result = result_type{};
        update_value(n1.value(), n2.value(), result);
        update_dvalues(indices_n1_only{}, n1, n2.value(), result);
        update_dvalues(indices_n2_only{}, n1.value(), n2, result);
        update_dvalues(indices_inner{}, n1, n2, result);
        return result;
    }

  protected:
    /// @brief Retrieves the derived class instance.
    auto self() const
    {
        return static_cast<const Derived *>(this);
    }

    /// @brief Updates the value of the result.
    template <class N>
    void update_value(const T &v1, const T &v2, N &n) const
    {
        n.value(self()->value(v1, v2));
    }

    /// @brief Updates the derivative values.
    template <size_t D, class N1, class N2, class N>
    void update_dvalue(const N1 &n1, const N2 &n2, N &n) const
    {
        if constexpr (std::is_same_v<N1, T>)
        {
            n.template dvalue<D>(self()->dvalue(n1, make_duo<D>(n2)));
        }
        else if constexpr (std::is_same_v<N2, T>)
        {
            n.template dvalue<D>(self()->dvalue(make_duo<D>(n1), n2));
        }
        else
        {
            n.template dvalue<D>(self()->dvalue(make_duo<D>(n1), make_duo<D>(n2)));
        }
    }

  private:
    /// @brief Updates all derivative values.
    /// @tparam Dn Differentiation orders.
    /// @tparam N1 The first number type.
    /// @tparam N2 The second number type.
    /// @tparam N The result number type.
    /// @param n1 The first input number.
    /// @param n2 The second input number.
    /// @param n The result number.
    template <size_t... Dn, class N1, class N2, class N>
    void update_dvalues(const indices<Dn...>, const N1 &n1, const N2 &n2, N &n) const
    {
        (update_dvalue<Dn>(n1, n2, n), ...);
    }
};
} // namespace dual
