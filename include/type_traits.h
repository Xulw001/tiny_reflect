/**
 * @file type_traits.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Provides type traits for various C++ types.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <string>
#include <vector>

#include "object.h"
#include "type_enum.h"

namespace reflect {

/**
 * @brief A template struct to determine the type traits of various types.
 *
 * This struct specializes for fundamental types, std::string, and types derived from ObjectInternal.
 * Each specialization provides a corresponding TypeEnum value that represents the type.
 *
 * @tparam T The type for which the traits are being determined.
 * @tparam void_type A default parameter used for SFINAE (Substitution Failure Is Not An Error).
 */
template <typename T, typename = void>
struct TypeTraits;

/**
 * @brief Specialization for bool type.
 */
template <>
struct TypeTraits<bool> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_BOOL;
};

/**
 * @brief Specialization for char type.
 */
template <>
struct TypeTraits<char> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_INT8;
};

/**
 * @brief Specialization for unsigned char type.
 */
template <>
struct TypeTraits<unsigned char> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_UINT8;
};

/**
 * @brief Specialization for short type.
 */
template <>
struct TypeTraits<short> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_INT16;
};

/**
 * @brief Specialization for unsigned short type.
 */
template <>
struct TypeTraits<unsigned short> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_UINT16;
};

/**
 * @brief Specialization for int type.
 */
template <>
struct TypeTraits<int> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_INT32;
};

/**
 * @brief Specialization for unsigned int type.
 */
template <>
struct TypeTraits<unsigned int> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_UINT32;
};

/**
 * @brief Specialization for long long type.
 */
template <>
struct TypeTraits<long long> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_INT64;
};

/**
 * @brief Specialization for unsigned long long type.
 */
template <>
struct TypeTraits<unsigned long long> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_UINT64;
};

/**
 * @brief Specialization for long type.
 */
template <>
struct TypeTraits<long> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_LONG;
};

/**
 * @brief Specialization for unsigned long type.
 */
template <>
struct TypeTraits<unsigned long> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_ULONG;
};

/**
 * @brief Specialization for float type.
 */
template <>
struct TypeTraits<float> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_FLOAT;
};

/**
 * @brief Specialization for double type.
 */
template <>
struct TypeTraits<double> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_DOUBLE;
};

/**
 * @brief Specialization for std::string type.
 */
template <>
struct TypeTraits<std::string> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_STRING;
};

/**
 * @brief Specialization for types derived from ObjectInternal.
 *
 * This specialization allows for the identification of user-defined types that inherit from ObjectInternal.
 */
template <typename T>
struct TypeTraits<T, typename std::enable_if<std::is_base_of<ObjectInternal, T>::value>::type> {
    static constexpr TypeEnum value = TypeEnum::CPPTYPE_OBJECT;
};

}  // namespace reflect

#endif