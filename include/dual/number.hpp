#pragma once

#include <tuple>

/// @namespace dual
/// @brief Namespace for dual number representation and automatic differentiation.
namespace dual
{
    /// @class number
    /// @brief Represents a dual number used for automatic differentiation.
    ///
    /// @tparam T The underlying numeric type (e.g., double, float).
    /// @tparam Dn Variadic template parameter representing derivative indices.
    template <class T, size_t... Dn>
    struct number
    {
        /// @brief Default constructor initializes value to zero.
        explicit number() = default;
        
        /// @brief Constructs a number with an initial value.
        /// @param init The initial value of the number.
        explicit number(const T &init) : value_{init}, dvalues_{} {}

        /// @brief Implicit conversion to the underlying type.
        /// @return The stored value of the number.
        operator const T &() const
        {
            return value_;
        }

        /// @brief Gets the value of the number.
        /// @return A constant reference to the value.
        auto value() const -> const auto &
        {
            return value_;
        }
        
        /// @brief Sets the value of the number.
        /// @param value The new value to set.
        void value(const T &value)
        {
            value_ = value;
        }

        /// @brief Gets the derivative value for a specific index.
        /// @tparam D The derivative index.
        /// @return A constant reference to the derivative value.
        template <size_t D>
        auto dvalue() const -> const auto &
        {
            return std::get<dvalue_type<D>>(dvalues_).value;
        }

        /// @brief Sets the derivative value for a specific index.
        /// @tparam D The derivative index.
        /// @param value The new derivative value.
        template <size_t D>
        void dvalue(const T &value)
        {
            std::get<dvalue_type<D>>(dvalues_).value = value;
        }

    protected:
        /// @brief Internal structure to store derivative values.
        /// @tparam D The derivative index.
        template <size_t D>
        struct dvalue_type
        {
            T value{1}; ///< Stores the derivative value, initialized to 1.
        };

    private:
        T value_; ///< The primary value of the number.
        std::tuple<dvalue_type<Dn>...> dvalues_; ///< Tuple storing derivatives for different indices.
    };
} // namespace dual
