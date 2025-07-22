#pragma once

#include <tuple>

namespace dual
{
/// @brief Represents a scalar value with associated derivative storage.
///
/// @tparam T The underlying scalar type (e.g., float, double, etc.).
/// @tparam Dn Parameter pack of derivative indices used to define associated 
///            derivative storage.
template <class T, std::size_t... Dn>
struct number
{
    /// @brief Type alias for the underlying scalar type.
    using value_type = T;

    /// @brief Default constructor.
    explicit number() = default;

    /// @brief Constructor initializing the scalar value.
    /// @param init The initial value to store.
    explicit number(const T &init) : value_{init}, dvalues_{} {}

    /// @brief Implicit conversion to the stored scalar value.
    /// @return Constant reference to the stored value.
    operator const T &() const 
    { 
        return value_; 
    }

    /// @brief Returns the stored scalar value.
    /// @return Constant reference to the stored value.
    auto value() const -> const auto & 
    { 
        return value_; 
    }

    /// @brief Sets the stored scalar value.
    /// @param value The value to store.
    void value(const T &value) 
    { 
        value_ = value; 
    }

    /// @brief Retrieves the value of the D-th associated derivative.
    /// @tparam D The derivative index to retrieve (must be in Dn...).
    /// @return Constant reference to the stored derivative value.
    template <std::size_t D>
    auto dvalue() const -> const auto &
    {
        return std::get<dvalue_type<D>>(dvalues_).value;
    }

    /// @brief Sets the value of the D-th associated derivative.
    /// @tparam D The derivative index to set (must be in Dn...).
    /// @param value The value to store for the derivative.
    template <std::size_t D>
    void dvalue(const T &value)
    {
        std::get<dvalue_type<D>>(dvalues_).value = value;
    }

protected:
    /// @brief Helper type representing the storage for a specific derivative.
    /// @tparam D Derivative index.
    template <std::size_t D>
    struct dvalue_type
    {
        /// @brief The stored value of the derivative, initialized to 1 by default.
        T value{1.0};
    };

private:
    /// @brief The stored scalar value.
    T value_{};

    /// @brief Tuple of derivative value storage.
    std::tuple<dvalue_type<Dn>...> dvalues_;
};

/// @brief Type trait to detect if a type is a specialization of number<T, S>.
/// @tparam T Type to test.
template <class T>
struct is_number : std::false_type
{
};

/// @brief Specialization of is_number for number<T, S>.
/// @tparam T Value type.
/// @tparam S Derivative index parameter.
template <class T, std::size_t... Ds>
struct is_number<number<T, Ds...>> : std::true_type
{
};

/// @brief Helper variable template for is_number.
/// @tparam T Type to test.
template <class T>
constexpr bool is_number_v = is_number<T>::value;

template <class T>
struct is_number_like : std::is_arithmetic<T>
{
};
template <class T, std::size_t... Ds>
struct is_number_like<number<T, Ds...>> : std::true_type
{
};

template <class T>
constexpr bool is_number_like_v = is_number_like<T>::value;

} // namespace dual
