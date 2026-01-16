/**
 * @file decimal.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the Decimal class, which provides methods for conversion
 *        and retrieval of the stored value.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_DECIMAL_H
#define TYPE_DECIMAL_H
#include <type_traits>

#include "object.h"

namespace reflect {

/**
 * @brief A class representing a decimal number that can store either a float or a double.
 *
 * This class inherits from ObjectInternal and uses a union to store the decimal value
 * as either a float or a double, depending on the precision required. It provides methods
 * to convert the stored value to float or double and to retrieve the value as a specified
 * type.
 */
struct Decimal : public ObjectInternal {
   private:
    union {
        float f;
        double d;
    };

   public:
    /**
     * @brief Constructs a Decimal object from a floating-point value.
     *
     * @tparam T The type of the floating-point value (float or double).
     * @param v The floating-point value to be stored in the Decimal object.
     *
     * This constructor is enabled only for floating-point types.
     */
    template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>>
    Decimal(const T& v) : d(v) {}

    /**
     * @brief Converts the stored value to a float.
     *
     * @return The float representation of the stored decimal value.
     */
    float to_float() const { return f; }

    /**
     * @brief Converts the stored value to a double.
     *
     * @return The double representation of the stored decimal value.
     */
    double to_double() const { return d; }

    /**
     * @brief Retrieves the stored value as a specified type.
     *
     * @tparam T The type to which the stored value should be converted.
     * @return The stored value converted to the specified type.
     */
    template <typename T>
    T get() const {
        return static_cast<T>(d);
    }
};

}  // namespace reflect

#endif