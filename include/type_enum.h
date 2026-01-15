/**
 * @file type_enum.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Enumeration of C++ data types for reflection
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_ENUM_H
#define TYPE_ENUM_H

namespace reflect {
/**
 * @enum TypeEnum
 *
 * This enumeration defines various C++ data types that can be used in
 * reflection systems. Each enumerator corresponds to a specific C++ type.
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
    CPPTYPE_OBJECT,  //

    MAX_CPPTYPE = 14,

};
}  // namespace reflect

#endif