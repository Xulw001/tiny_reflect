/**
 * @file type_enum.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief C++ basic type enum + reflection type traits
 * @version 0.2
 * @date 2026-02-28
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_ENUM_H
#define TYPE_ENUM_H

#include <string>

namespace reflect {
/**
 * @enum TypeEnum
 * @brief C++ basic type enumeration (reflection system)
 * @details Maps C++ primitive types to unique IDs for reflection
 */
enum TypeEnum {
    CPPTYPE_BOOL,    //
    CPPTYPE_INT8,    //
    CPPTYPE_UINT8,   //
    CPPTYPE_INT16,   //
    CPPTYPE_UINT16,  //
    CPPTYPE_INT32,   //
    CPPTYPE_UINT32,  //
    CPPTYPE_INT64,   //
    CPPTYPE_UINT64,  //
    CPPTYPE_LONG,    //
    CPPTYPE_ULONG,   //
    CPPTYPE_DOUBLE,  //
    CPPTYPE_FLOAT,   //
    CPPTYPE_STRING,  //

    CPPTYPE_MAX = 14,

};

/**
 * @struct is_internel_type
 * @brief Type trait for internal basic types (reflection)
 * @tparam T Type to check
 * @details Indicates if T is a basic type (true/false); provides type ID
 */
template <typename T>
struct is_internel_type : std::false_type {
    static constexpr std::size_t type_id = CPPTYPE_MAX;
};

/**
 * @brief Specialization for bool
 */
template <>
struct is_internel_type<bool> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_BOOL;
};

/**
 * @brief Specialization for char (int8)
 */
template <>
struct is_internel_type<char> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_INT8;
};

/**
 * @brief Specialization for unsigned char (uint8)
 */
template <>
struct is_internel_type<unsigned char> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_UINT8;
};

/**
 * @brief Specialization for short (int16)
 */
template <>
struct is_internel_type<short> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_INT16;
};

/**
 * @brief Specialization for unsigned short (uint16)
 */
template <>
struct is_internel_type<unsigned short> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_UINT16;
};

/**
 * @brief Specialization for int (int32)
 */
template <>
struct is_internel_type<int> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_INT32;
};

/**
 * @brief Specialization for unsigned int (uint32)
 */
template <>
struct is_internel_type<unsigned int> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_UINT32;
};

/**
 * @brief Specialization for long long (int64)
 */
template <>
struct is_internel_type<long long> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_INT64;
};

/**
 * @brief Specialization for unsigned long long (uint64)
 */
template <>
struct is_internel_type<unsigned long long> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_UINT64;
};

/**
 * @brief Specialization for long
 */
template <>
struct is_internel_type<long> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_LONG;
};

/**
 * @brief Specialization for unsigned long (ulong)
 */
template <>
struct is_internel_type<unsigned long> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_ULONG;
};

/**
 * @brief Specialization for double
 */
template <>
struct is_internel_type<double> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_DOUBLE;
};

/**
 * @brief Specialization for float
 */
template <>
struct is_internel_type<float> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_FLOAT;
};

/**
 * @brief Specialization for std::string
 */
template <>
struct is_internel_type<std::string> : std::true_type {
    static constexpr std::size_t type_id = CPPTYPE_STRING;
};

}  // namespace reflect

#endif