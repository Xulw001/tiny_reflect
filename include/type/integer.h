/**
 * @file integer.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the Integer class, which provides methods for
 *        conversion and retrieval of the stored integer value in various formats.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_INTEGER_H
#define TYPE_INTEGER_H

#include <type_traits>

#include "object.h"

namespace reflect {

/**
 * @class Integer
 * @brief A class that represents an integer value, supporting both signed and unsigned types.
 *
 * This class uses a union to store different integer types and provides methods to convert
 * and retrieve the stored value in various formats. It is designed to handle integral types
 * efficiently while maintaining type safety.
 *
 * @tparam T The integral type to be stored in the Integer class. Must be a signed or unsigned integral type.
 *
 * @note The class inherits from ObjectInternal, which may provide additional functionality.
 */
struct Integer : public ObjectInternal {
   private:
    bool is_unsigned_ = false;  ///< Indicates whether the stored integer is unsigned.

    union {
        char c;
        short s;
        int i;
        long l;
        long long ll;

        unsigned char uc;
        unsigned short us;
        unsigned int ui;
        unsigned long ul;
        unsigned long long ull;
    };

   public:
    /**
     * @brief Constructs an Integer object from a given integral value.
     *
     * @tparam T The type of the value being passed in. Must be an integral type.
     * @param val The integral value to be stored in the Integer object.
     */
    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    Integer(T val) : is_unsigned_(std::is_unsigned<T>::value) {
        if (is_unsigned_)
            ull = val;
        else
            ll = val;
    }

    /**
     * @brief Converts the stored value to int8_t.
     * @return The stored value as int8_t.
     */
    int32_t to_int8() const { return c; }

    /**
     * @brief Converts the stored value to int16_t.
     * @return The stored value as int16_t.
     */
    int64_t to_int16() const { return s; }

    /**
     * @brief Converts the stored value to int32_t.
     * @return The stored value as int32_t.
     */
    int32_t to_int32() const { return i; }

    /**
     * @brief Converts the stored value to int64_t.
     * @return The stored value as int64_t.
     */
    int64_t to_int64() const { return ll; }

    /**
     * @brief Converts the stored value to uint8_t.
     * @return The stored value as uint8_t.
     */
    uint32_t to_uint8() const { return uc; }

    /**
     * @brief Converts the stored value to uint16_t.
     * @return The stored value as uint16_t.
     */
    uint64_t to_uint16() const { return us; }

    /**
     * @brief Converts the stored value to uint32_t.
     * @return The stored value as uint32_t.
     */
    uint32_t to_uint32() const { return ui; }

    /**
     * @brief Converts the stored value to uint64_t.
     * @return The stored value as uint64_t.
     */
    uint64_t to_uint64() const { return ull; }

    /**
     * @brief Converts the stored value to long.
     * @return The stored value as long.
     */
    int32_t to_long() const { return l; }

    /**
     * @brief Converts the stored value to unsigned long.
     * @return The stored value as unsigned long.
     */
    int64_t to_ulong() const { return ul; }

    /**
     * @brief Retrieves the stored value as the specified type.
     *
     * @tparam T The type to which the stored value should be converted.
     * @return The stored value cast to the specified type.
     */
    template <typename T>
    T get() const {
        return static_cast<T>(is_unsigned_ ? ull : ll);
    }
};

}  // namespace reflect

#endif