/**
 * @file reflect.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Public API for reflection system (type registration and loading)
 * @version 0.2
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REFLECT_H
#define REFLECT_H

#include "type/exception.h"
#include "type_info.h"

namespace reflect {

/**
 * @brief Register type T with name
 * @tparam T Type to register (object type only)
 * @param name Type name (unique)
 * @return Type& Registered type reference
 */
template <typename T>
Type& regist(const char* name) {
    return TypeInfo::GetInstance().regist<T>(name);
}

/**
 * @brief Load type by name
 * @param name Type name to look up
 * @return const Type& Matching type (or default_ if not found)
 */
const Type& load(const char* name) {
    return TypeInfo::GetInstance().load(name);
}

/**
 * @brief Load type by type ID
 * @param type_id Unique type ID
 * @return const Type& Matching type
 * @throws ReflectException If type with given ID is not found
 */
const Type& load(const size_t type_id) {
    const char* name = TypeIdInfo::GetInstance().get_type_name(type_id);
    if (name) {
        return load(name);
    }
    throw ReflectException::format("class %s not found!", name);
};
}  // namespace reflect

#endif