/**
 * @file reflect.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file provides the entry point for the reflection system.
 * @version 0.1
 * @date 2026-01-16
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REFLECT_H
#define REFLECT_H

#include "type_info.h"

namespace reflect {

template <typename T>
Type& regist(const char* name) {
    return TypeInfo::GetInstance().regist<T>(name);
}

const Type& load(const char* name) {
    return TypeInfo::GetInstance().load(name);
}

const Type& load(const size_t type_id) {
    const char* name = TypeIdInfo::GetInstance().get_type_name(type_id);
    if (name == nullptr) throw "class not found!";
    return load(name);
};
}  // namespace reflect

#endif